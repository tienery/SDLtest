#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "mintSDL/display/anim.h"
#include "mintSDL/display/texture.h"
#include "mintSDL/display/trans.h"
#include "mintSDL/maths/geom.h"

MintAnimMan* mint_AnimManSetup(MintTexture* mintTexture)
{
	MintAnimMan* animMan = (MintAnimMan*)malloc(sizeof(MintAnimMan));

	animMan->totalAnims = 0;
	animMan->currentAnim = NULL;
	animMan->mintTexture = mintTexture;

	return animMan;
}

void mint_AnimManInit(MintAnimMan* animMan, int totalAnims)
{
	animMan->anims = (MintAnim*)malloc(sizeof(MintAnim) * totalAnims);
	animMan->totalAnims = totalAnims;

	int i;
	for (i = 0; i < totalAnims; i++) animMan->anims[i].man = animMan;
}

void mint_AnimCreate(MintAnimMan* animMan, int index, char* name, int totalFrames)
{
	MintAnim* anim = mint_AnimGetByIndex(animMan, index);

	anim->name = name;
	anim->frameRects = (SDL_Rect*)malloc(sizeof(SDL_Rect) * totalFrames);
	anim->totalFrames = totalFrames;
	anim->totalFrames = totalFrames;
}

void mint_AnimDefineFrame(MintAnim* anim, int frameNumber, int x, int y, int width, int height)
{
	anim->frameRects[frameNumber] = {x, y, width, height};
}

void mint_AnimDefineFrames(MintAnim* anim, SDL_Rect* frameRects)
{
	anim->frameRects = frameRects;
}

void mint_AnimDefineLinearStripFrames(MintAnim* anim, int frameWidth, char loop)
{
	int i;
	for (i = 0; i < anim->totalFrames; i++) {
		mint_AnimDefineFrame(anim, i, frameWidth * i, 0, frameWidth, mint_TransGetHeight(anim->man->mintTexture->trans));
	}

	anim->currentFrame = 0;
	anim->loop = loop;

	anim->man->mintTexture->rend->_clipRect = &anim->frameRects[0];
	anim->man->mintTexture->trans->_width = anim->frameRects[0].w;
	anim->man->mintTexture->trans->_height = anim->frameRects[0].h;
}

void mint_AnimUpdate(MintAnimMan* animMan, float elapsed)
{
	
}

void mint_AnimUpdateClip(MintAnimMan* animMan)
{
	animMan->mintTexture->rend->_clipRect = &animMan->currentAnim->frameRects[animMan->currentAnim->currentFrame];	
}

void mint_AnimUpdateAsButton(MintAnimMan* animMan, MintInput* input)
{
	SDL_Rect rect = { animMan->mintTexture->trans->_x, animMan->mintTexture->trans->_y, animMan->mintTexture->trans->_width, animMan->mintTexture->trans->_height };
	if (mint_GeomPointInRect(&input->mousePoint, &rect)) {
		if (input->mouseButtonStatus[0]) {
			mint_AnimGotoFrame(animMan, 2);
		} else {
			mint_AnimGotoFrame(animMan, 1);
		}
	} else {
		mint_AnimGotoFrame(animMan, 0);
	}
}

MintAnim* mint_AnimGetByIndex(MintAnimMan* animMan, int index)
{
	return &animMan->anims[index];
}

void mint_AnimPlay(MintAnim* anim)
{
	anim->man->currentAnim = anim;
}

void mint_AnimNextFrame(MintAnimMan* animMan)
{
	if (animMan->currentAnim->currentFrame < animMan->currentAnim->totalFrames - 1) {
		animMan->currentAnim->currentFrame++;
	} else if (animMan->currentAnim->loop) {
		animMan->currentAnim->currentFrame = 0;
	}
	
	mint_AnimUpdateClip(animMan);
}

void mint_AnimGotoFrame(MintAnimMan* animMan, int index)
{
	animMan->currentAnim->currentFrame = index;
	mint_AnimUpdateClip(animMan);
}

void mint_AnimManFree(MintAnimMan* animMan)
{
	int i;
	for (i = 0; i < animMan->totalAnims; i++) {
		free(animMan->anims[i].frameRects);
		animMan->anims[i].frameRects = NULL;
		
		free(animMan->anims);
		animMan->anims = NULL;
	}

	free(animMan);
	animMan = NULL;
}
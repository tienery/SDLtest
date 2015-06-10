#ifndef PHYS_H
#define PHYS_H

struct MintFloatPoint;
struct MintPhys;

#include <SDL.h>
#include "mintSDL/display/texture.h"

struct MintDoublePoint {
	double x;
	double y;
};

struct MintPhys {
	MintTexture* mintTexture;
	MintDoublePoint velocity;
	MintDoublePoint accel;
	MintDoublePoint drag;
	MintDoublePoint maxVelocity;
};

MintPhys* mint_PhysCreate(MintTexture* mintTexture);
void mint_PhysUpdate(MintPhys* phys, double elapsed);
double mint_PhysComputeVelocity(double velocity, double accel, double drag, double max, double elapsed);
void mint_PhysFree(MintPhys* phys);

#endif
#include <SDL.h>
#include "mintSDL/maths/geom.h"

char mint_GeomPointInRect(SDL_Point* point, SDL_Rect* rect)
{
	// Corners in ax,ay,bx,by,dx,dy
	// Point in x, y

	int ax = rect->x;
	int ay = rect->y;
	int bx = rect->x + rect->w;
	int by = rect->y;
	int dx = rect->x;
	int dy = rect->y + rect->h;

	int bax = bx - ax;
	int bay = by - ay;
	int dax = dx - ax;
	int day = dy - ay;

	if ((point->x - ax) * bax + (point->y - ay) * bay < 0) return 0;
	if ((point->x - bx) * bax + (point->y - by) * bay > 0) return 0;
	if ((point->x - ax) * dax + (point->y - ay) * day < 0) return 0;
	if ((point->x - dx) * dax + (point->y - dy) * day > 0) return 0;

	return 1;
}

char mint_GeomRectInRect(SDL_Rect* a, SDL_Rect* b)
{
	if(a->x + a->w < b->x || a->x > b->x + b->w) return 0;
	if(a->y + a->h < b->y || a->y > b->y + b->h) return 0;

	return 1;
}
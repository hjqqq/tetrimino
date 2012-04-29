#ifndef UTILITY_H
#define UTILITY_H

#include "SDL_image.h"
#include "stabledata.h"

SDL_Surface *image_load(const char *file);
inline const SDL_Rect get_rect(const SDL_Surface *surface);
inline void cleanMap(int *map[10]);

const SDL_Rect get_rect(const SDL_Surface *surface)
{
    const SDL_Rect rect = {0, 0, surface->w, surface->h};
    return rect;
}

void cleanMap(int *mapData[10])
{
    for (int i = 0; i != StableData::mapSize.x; ++i)
	for (int j = 0; j != StableData::mapSize.y; ++j)
	    mapData[i][j] = 0;
}

#endif 

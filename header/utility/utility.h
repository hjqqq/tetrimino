#ifndef UTILITY_H
#define UTILITY_H

#include <cstdlib>
#include <string>

#include "SDL_image.h"
#include "resourcedata.h"
#include "optiondata.h"

SDL_Surface *image_load(const char *file);
inline const SDL_Rect get_rect(const SDL_Surface *surface);
inline Uint32 SDL_Color2Uint32(const SDL_Color &color);

const SDL_Rect get_rect(const SDL_Surface *surface)
{
    const SDL_Rect rect = {0, 0, surface->w, surface->h};
    return rect;
}

Uint32 SDL_Color2Uint32(const SDL_Color &color)
{
    return SDL_MapRGB(ResourceData::display->format,
		      color.r,
		      color.g,
		      color.b);
}

inline int randInt(int begin, int end)
{
    int length = end - begin;
    return std::rand() % length + begin;
}

void doubleToString(double, std::string &);
#endif 

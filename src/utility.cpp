#include "utility.h"

SDL_Surface *image_load(const char *file)
{
    SDL_Surface *image_orig = IMG_Load(file);
    SDL_Surface *image = SDL_DisplayFormat(image_orig);
    SDL_FreeSurface(image_orig);
    return image;
}

const SDL_Rect get_rect(const SDL_Surface *surface)
{
    const SDL_Rect rect = {0, 0, surface->w, surface->h};
    return rect;
}

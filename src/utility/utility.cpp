#include "utility.h"

SDL_Surface *image_load(const char *file)
{
    SDL_Surface *image_orig = IMG_Load(file);
    SDL_Surface *image = SDL_DisplayFormat(image_orig);
    SDL_FreeSurface(image_orig);
    return image;
}


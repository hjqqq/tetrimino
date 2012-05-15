#ifndef RESOURCEDATA_H
#define RESOURCEDATA_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "clock.h"
#include "sound.h"

namespace ResourceData{
    extern SDL_Surface *display;
    extern SDL_Surface *background;
    extern TTF_Font *font;
    extern Clock *clock;
    extern Sound *sound;
};

#endif

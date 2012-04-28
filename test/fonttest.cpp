#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"
#include "color.h"

/**
   @file main.cpp
 */

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    SDL_Surface *display = SDL_SetVideoMode(400, 300, 0, SDL_SWSURFACE);

    TTF_Font* font = TTF_OpenFont("res/MINYN___.ttf", 30);
    SDL_Color color = orchid;
    SDL_Surface *fontSurface = TTF_RenderText_Blended(
	font,
	"HelloWorld!!!",
	color);

    SDL_BlitSurface(fontSurface, 0, display, 0);
    SDL_FreeSurface(fontSurface);

    SDL_Event event;
    while (true){
	while (SDL_PollEvent(&event)){
	    switch (event.type){
	    case SDL_QUIT:
		TTF_Quit();
		SDL_Quit();
		return 0;
	    }
	}
	SDL_UpdateRect(display, 0, 0, 0, 0);
    }
    
    return 0;
}

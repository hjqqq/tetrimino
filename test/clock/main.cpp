#include <ctime>
#include <cstdlib>
#include <iostream>

#include "SDL.h"
#include "SDL_draw.h"

#include "color.h"
#include "clock.h"
#include "timer.h"

int main()
{
    std::srand(std::time(NULL));


    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface *display = SDL_SetVideoMode(800, 600, 0, SDL_SWSURFACE);

    Clock clock(60);
    Timer backTimer = Timer(3000);
    Counter *backCounter = clock.addCounter(300);
    Counter *changeColorCounter = clock.addCounter(50);
    Counter *drawCounter = clock.addCounter(2);

    SDL_Event event;
    Sint16 x, y;
    Uint16 r;
    
    SDL_Color color = {rand() % 255, rand() % 255, rand() % 255};
    Uint32 colorInt = SDL_MapRGB(display->format, color.r, color.g, color.b);
    SDL_FillRect(display, NULL, colorInt);
	
    while (true){
	while (SDL_PollEvent(&event)){
	    switch (event.type){
	    case SDL_QUIT:
		return 0;
	    }
	}
	if (backTimer.checkTimeOut()){
	    SDL_FillRect(display, NULL, colorInt);
	    backCounter->reset();
	    backTimer.reset();
	}
	if (!changeColorCounter->getRemain()){
	    color = {rand() % 255, rand() % 255, rand() % 255};
	    colorInt = SDL_MapRGB(display->format, color.r, color.g, color.b);
	    changeColorCounter->reset();
	}
	if (!drawCounter->getRemain()){
	    x = rand() % 700 + 50;
	    y = rand() % 500 + 50;
	    r = rand() % 50;
	    Draw_FillCircle(display, x, y, r, colorInt);
	    drawCounter->reset();
	}
	
	SDL_UpdateRect(display, 0, 0, 0, 0);
	clock.tick();
    }
    return 0;
}

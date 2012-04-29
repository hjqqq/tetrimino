#include <iostream>

#include "tetrimino.h"
#include "stabledata.h"
#include "optiondata.h"
#include "menuholder.h"
#include "color.h"

Tetrimino::Tetrimino()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();
    loadResource();
    
    mainloop();
}

Tetrimino::~Tetrimino(){
    releaseResource();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Tetrimino::loadResource()
{
    OptionData::display = SDL_SetVideoMode(
	StableData::screenSize.x,
	StableData::screenSize.y,
	0,
	SDL_SWSURFACE);
    OptionData::background = image_load(
	StableData::backgroundFile.c_str());
    OptionData::font = TTF_OpenFont(
	StableData::fontFile.c_str(), 30);
}

void Tetrimino::releaseResource()
{
    TTF_CloseFont(OptionData::font);
    SDL_FreeSurface(OptionData::background);
}

void Tetrimino::mainloop()
{
    while (true){
	switch (OptionData::tetriminoStatus){
	case OptionData::MENULOOP:
	    menuloop();
	    break;
	case OptionData::GAMELOOP:
	    gameloop();
	    break;
	case OptionData::QUIT:
	    return;
	}
    }
}

void Tetrimino::menuloop()
{
    MenuHolder menuHolder;
    SDL_Event event;
    while (OptionData::menuHolderStatus != OptionData::QUITMENU){
	while (SDL_PollEvent(&event)){
	    if (event.type == SDL_QUIT){
		OptionData::tetriminoStatus = OptionData::QUIT;
		return ;
	    }
	    menuHolder.handleEvent(event);
	}
	SDL_BlitSurface(OptionData::background, 0,
			OptionData::display, 0);
	menuHolder.update();
	SDL_UpdateRect(OptionData::display, 0, 0, 0, 0);
    }
}

void Tetrimino::gameloop()
{
    SDL_Event event;
    while (OptionData::gameHolderStatus != OptionData::QUITGAME){
	while (SDL_PollEvent(&event)){
	    if (event.type == SDL_QUIT){
		OptionData::tetriminoStatus = OptionData::QUIT;
		return ;
	    }
	}
	SDL_BlitSurface(OptionData::background, 0,
			OptionData::display, 0);
	SDL_UpdateRect(OptionData::display, 0, 0, 0, 0);
    }
    std::cout << "here is game loop" << std::endl;
}




#include <cstdlib>
#include <ctime>
#include <iostream>

#include "tetrimino.h"
#include "stabledata.h"
#include "optiondata.h"
#include "resourcedata.h"
#include "clock.h"
#include "menuholder.h"
#include "gameholder.h"
#include "color.h"
#include "setting.h"

Tetrimino::Tetrimino() : menu_setting("res/user_settings.txt")
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
    menu_setting.loadSetting();
    std::srand(std::time(NULL));
    ResourceData::display = SDL_SetVideoMode(
	StableData::screenSize.x,
	StableData::screenSize.y,
	0,
	SDL_SWSURFACE);
    ResourceData::background = image_load(
	StableData::backgroundFile.c_str());
    ResourceData::font = TTF_OpenFont(
	StableData::fontFile.c_str(), 30);
    ResourceData::clock = new Clock(StableData::fps);
    ResourceData::sound = new Sound();
}

void Tetrimino::releaseResource()
{
    TTF_CloseFont(ResourceData::font);
    SDL_FreeSurface(ResourceData::background);
    delete ResourceData::sound;
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
	SDL_BlitSurface(ResourceData::background, 0,
			ResourceData::display, 0);
	menuHolder.update();
	SDL_UpdateRect(ResourceData::display, 0, 0, 0, 0);
	ResourceData::clock->tick();
    }
    OptionData::menuHolderStatus = OptionData::MAINMENU;
}

void Tetrimino::gameloop()
{
    initPlayerData1();
    initPlayerData2();
    initPlayerData3();
    GameHolder gameHolder;
    SDL_Event event;
    while (OptionData::gameHolderStatus != OptionData::QUITGAME){
	while (SDL_PollEvent(&event)){
	    if (event.type == SDL_QUIT){
		OptionData::tetriminoStatus = OptionData::QUIT;
		return ;
	    }
	    gameHolder.handleEvent(event);
	}
	gameHolder.update();
	SDL_UpdateRect(ResourceData::display, 0, 0, 0, 0);
	ResourceData::clock->tick();
    }
    OptionData::gameHolderStatus = OptionData::READY;
    OptionData::tetriminoStatus = OptionData::MENULOOP;
}


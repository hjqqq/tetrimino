#include "optiondata.h"

using namespace OptionData;

SDL_Surface *OptionData::display = NULL;
SDL_Surface *OptionData::background = NULL;
TTF_Font *OptionData::font = NULL;
Clock *OptionData::clock = NULL;
    
TetriminoStatus OptionData::tetriminoStatus = GAMELOOP;
    
MenuHolderStatus OptionData::menuHolderStatus = MAINMENU;

GameHolderStatus OptionData::gameHolderStatus = LOCK;
Uint32 OptionData::areDelayTime = 200;
Uint32 OptionData::lockDelayTime = 500;

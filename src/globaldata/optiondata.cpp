#include "optiondata.h"

using namespace OptionData;

SDL_Surface *OptionData::display = NULL;
SDL_Surface *OptionData::background = NULL;
TTF_Font *OptionData::font = NULL;
    
TetriminoStatus OptionData::tetriminoStatus = MENULOOP;
    
MenuHolderStatus OptionData::menuHolderStatus = MAINMENU;

GameHolderStatus OptionData::gameHolderStatus = STARTGAME;

#include "optiondata.h"

SDL_Surface *OptionData::display = NULL;
SDL_Surface *OptionData::background = NULL;
TTF_Font *OptionData::font = NULL;
OptionData::TetriminoStatus OptionData::tetriminoStatus = GAMELOOP;
OptionData::MenuHolderStatus OptionData::menuHolderStatus = MAINMENU;
OptionData::GameHolderStatus OptionData::gameHolderStatus = STARTGAME;

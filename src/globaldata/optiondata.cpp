#include "blockdata.h"
#include "optiondata.h"

using namespace OptionData;

SDL_Surface *OptionData::display = NULL;
SDL_Surface *OptionData::background = NULL;
TTF_Font *OptionData::font = NULL;
Clock *OptionData::clock = NULL;

TetriminoStatus OptionData::tetriminoStatus = MENULOOP;
    
MenuHolderStatus OptionData::menuHolderStatus = MAINMENU;

GameHolderStatus OptionData::gameHolderStatus = START;

Uint32 OptionData::dasDelayTime = 200;

Uint32 OptionData::areDelayTime = 200;
Uint32 OptionData::lockDelayTime = 500;

// 单位为 G, 即每帧下降多少格
double OptionData::horizontalSpeed = 1;
double OptionData::normalDropSpeed = 0.05;
double OptionData::softDropSpeed = 0.5;

OptionData::RandomizerType OptionData::randomizerType = BAG;

int OptionData::history4Roll[4] = {
    BlockData::ZSHAPE,
    BlockData::SSHAPE,
    BlockData::ZSHAPE,
    BlockData::SSHAPE
};

bool OptionData::haveghost = true;
bool OptionData::haveholder = true;

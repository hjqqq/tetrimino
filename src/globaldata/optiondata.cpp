#include "blockdata.h"
#include "optiondata.h"

OptionData::TetriminoStatus OptionData::tetriminoStatus = GAMELOOP;
OptionData::MenuHolderStatus OptionData::menuHolderStatus = MAINMENU;
OptionData::GameStatus OptionData::gameStatus = RUN;

int OptionData::areDelayTime = 200;
int OptionData::lockDelayTime = 500;

int OptionData::playerSize;

PlayerData OptionData::playerData1;
PlayerData OptionData::playerData2;
PlayerData OptionData::playerData3;
PlayerData OptionData::playerData4;

PlayerData* OptionData::allPlayerData[StableData::playerSizeMax] = {
    &OptionData::playerData1,
    &OptionData::playerData2,
    &OptionData::playerData3,
    &OptionData::playerData4
};

int OptionData::ghostAlpha;

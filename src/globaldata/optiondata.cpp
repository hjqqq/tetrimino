#include "blockdata.h"
#include "optiondata.h"

OptionData::TetriminoStatus OptionData::tetriminoStatus = MENULOOP;
OptionData::MenuHolderStatus OptionData::menuHolderStatus = MAINMENU;
OptionData::GameHolderStatus OptionData::gameHolderStatus = READY;

int OptionData::minoPixSizeX = 20;
int OptionData::minoPixSizeY = 20;
Vector2<int> OptionData::minoPixSize(minoPixSizeX, minoPixSizeY);

int OptionData::areDelayTime = 200;
int OptionData::lockDelayTime = 800;

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

<<<<<<< HEAD
int OptionData::ghostAlpha = 50;
=======
int OptionData::ghostAlpha;
int OptionData::musicVolume;
int OptionData::chunkVolume;
>>>>>>> origin/master

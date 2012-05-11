#include <iostream>
#include "playerdata.h"
#include "utility.h"

PlayerData playerData1;

PlayerData playerData2;

void initPlayerData1()
{
    OptionData::playerData1.dasDelayTime = 100;

    OptionData::playerData1.horizontalSpeed = 0.3;
    OptionData::playerData1.normalDropSpeed = 0.05;
    OptionData::playerData1.softDropSpeed = 0.5;
    
    OptionData::playerData1.randomQueueDataIndex = 0;
    OptionData::playerData1.showPixPos = Vector2<int>(20, 20);
    OptionData::playerData1.randomizerType =
	PlayerData::HISTORY4ROLL;
    
    OptionData::playerData1.moveLeft = SDLK_j;
    OptionData::playerData1.moveRight = SDLK_l;
    OptionData::playerData1.rotateLeft = SDLK_a;
    OptionData::playerData1.rotateRight = SDLK_s;
    OptionData::playerData1.softDrop = SDLK_k;
    OptionData::playerData1.hardDrop = SDLK_i;
    OptionData::playerData1.hold = SDLK_d;
}

void initPlayerData2()
{
    OptionData::playerData2.dasDelayTime = 100;
			  
    OptionData::playerData2.horizontalSpeed = 0.3;
    OptionData::playerData2.normalDropSpeed = 0.05;
    OptionData::playerData2.softDropSpeed = 0.5;
    
    OptionData::playerData2.randomQueueDataIndex = 0;
    OptionData::playerData2.showPixPos = Vector2<int>(420, 20);
    OptionData::playerData1.randomizerType =
	PlayerData::HISTORY4ROLL;    
    
    OptionData::playerData2.moveLeft = SDLK_KP1;
    OptionData::playerData2.moveRight = SDLK_KP3;
    OptionData::playerData2.rotateLeft = SDLK_LEFT;
    OptionData::playerData2.rotateRight = SDLK_RIGHT;
    OptionData::playerData2.softDrop = SDLK_KP5;
    OptionData::playerData2.hardDrop = SDLK_KP2;
    OptionData::playerData2.hold = SDLK_UP;    
}

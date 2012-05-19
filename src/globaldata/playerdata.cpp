#include <iostream>
#include "playerdata.h"
#include "utility.h"

void initPlayerData1()
{
    OptionData::playerData1.dasDelayTime = 150;

    OptionData::playerData1.horizontalSpeed = 0.3;
    OptionData::playerData1.normalDropSpeed = 0.05;
    OptionData::playerData1.softDropSpeed = 0.5;
    
    OptionData::playerData1.randomQueueDataIndex = 1;
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
    OptionData::playerData2.dasDelayTime = 150;
			  
    OptionData::playerData2.horizontalSpeed = 0.3;
    OptionData::playerData2.normalDropSpeed = 0.05;
    OptionData::playerData2.softDropSpeed = 0.5;
    
    OptionData::playerData2.randomQueueDataIndex = 1;
    OptionData::playerData2.showPixPos = Vector2<int>(420, 20);
    
    //JJJ
    OptionData::playerData2.moveLeft = SDLK_j;
    OptionData::playerData2.moveRight = SDLK_l;
    OptionData::playerData2.rotateLeft = SDLK_u;
    OptionData::playerData2.rotateRight = SDLK_o;
    OptionData::playerData2.softDrop = SDLK_k;
    OptionData::playerData2.hardDrop = SDLK_i;
    OptionData::playerData2.hold = SDLK_SPACE;    
}

void initPlayerData3()
{
    OptionData::playerData3.dasDelayTime = 150;

    OptionData::playerData3.horizontalSpeed = 0.3;
    OptionData::playerData3.normalDropSpeed = 0.05;
    OptionData::playerData3.softDropSpeed = 0.5;

    OptionData::playerData3.randomQueueDataIndex = 1;
    OptionData::playerData3.showPixPos = Vector2<int>(20, 20);


    //ZT
    OptionData::playerData3.moveLeft = SDLK_KP1;
    OptionData::playerData3.moveRight = SDLK_KP3;
    OptionData::playerData3.rotateLeft = SDLK_LEFT;
    OptionData::playerData3.rotateRight = SDLK_RIGHT;
    OptionData::playerData3.softDrop = SDLK_KP5;
    OptionData::playerData3.hardDrop = SDLK_KP2;
    OptionData::playerData3.hold = SDLK_UP;
}

#include <iostream>
#include "playerdata.h"
#include "utility.h"

PlayerData playerData1;

PlayerData playerData2;

void initPlayerData1()
{
    playerData1.informationPos = Vector2<int>(50, 50);
    playerData1.mapPixRect = Rect<int>(300, 100,
				       StableData::mapSizeX * StableData::minoPixSizeX,
				       StableData::mapSizeY * StableData::minoPixSizeY);
    cleanMapData(playerData1.mapData);
    playerData1.mapData[0][19] = 1;
    playerData1.mapData[1][19] = 1;
    playerData1.mapData[3][19] = 1;
    
    playerData1.currentDirection = BlockData::NORTH;
    playerData1.currentBlockShape = BlockData::TSHAPE;
    playerData1.blockPos = Vector2<int>(3, 0);

    playerData1.moveLeft = SDLK_LEFT;
    playerData1.moveRight = SDLK_RIGHT;
    playerData1.rotateLeft = SDLK_z;
    playerData1.rotateRight = SDLK_x;
    playerData1.softDrop = SDLK_DOWN;
    playerData1.hardDrop = SDLK_UP;
    playerData1.hold = SDLK_c;
}

void initPlayerData2()
{
    
}

#include "playerdata.h"
#include "utility.h"

PlayerData playerData1;

PlayerData playerData2;

void initPlayerData1()
{
    playerData1.informationPos = Vector2<int>(50, 50);
    playerData1.mapRect = Rect<int>(300, 100,
				    StableData::mapSizeX * StableData::blockPixSizeX,
				    StableData::mapSizeY * StableData::blockPixSizeY);
    cleanMapData(playerData1.mapData);
    playerData1.mapData[0][19] = 1;
    playerData1.mapData[1][19] = 1;
    playerData1.mapData[3][19] = 1;
    
    BlockData::Direction currentDirection = BlockData::NORTH;
    BlockData::BlockShape currentBlockShape = BlockData::LSHAPE;

    playerData1.blockPixPos = playerData1.mapRect.getCenter();
}

void initPlayerData2()
{
    
}

#include "playerdata.h"
#include "utility.h"

PlayerData playerData1;

PlayerData playerData2;

void initPlayerData1()
{
    playerData1.informationPos = Vector2(50, 50);
    playerData1.mapPos = Vector2(300, 50);
    cleanMap(playerData1.mapData);
}

void initPlayerData2()
{
    
}

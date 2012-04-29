#ifndef PLAYERDATA_H
#define PLAYERDATA_H

#include <vector>

#include "stabledata.h"

struct PlayerData{
    Vector2 informationPos;
    Vector2 mapPos;
    int mapData[StableData::mapSizeX][StableData::mapSizeY];
};

extern PlayerData playerData1, playerData2;
void initPlayerData1();
void initPlayerData2();

#endif

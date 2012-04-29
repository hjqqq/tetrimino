#ifndef PLAYERDATA_H
#define PLAYERDATA_H

#include <vector>

#include "stabledata.h";

struct PlayerData{
    Vector2 informationPos;
    Vector2 mapPos;
    int mapData[StableData::mapSize.x][StableData::mapSize.y];
    std::vector<BlockData> blockPackage;
    
};

extern PlayerData playData1, playData2;

#endif

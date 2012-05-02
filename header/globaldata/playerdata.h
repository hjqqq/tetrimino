#ifndef PLAYERDATA_H
#define PLAYERDATA_H

#include <vector>

#include "SDL.h"

#include "stabledata.h"
#include "blockdata.h"
#include "vector2.h"
#include "rect.h"

struct PlayerData{
    Vector2<int> informationPos;
    
    Rect<int> mapPixRect;
    int mapData[StableData::mapSizeX][StableData::mapSizeY];

    BlockData::Direction currentDirection;
    BlockData::BlockShape currentBlockShape;
    Vector2<int> blockPos;

    SDLKey moveLeft;
    SDLKey moveRight;
    SDLKey rotateLeft;
    SDLKey rotateRight;
    SDLKey softDrop;
    SDLKey hardDrop;
    SDLKey hold;
};

extern PlayerData playerData1, playerData2;

void initPlayerData1();
void initPlayerData2();

inline void cleanMapData(int mapData[StableData::mapSizeX][StableData::mapSizeY]);


void cleanMapData(int mapData[StableData::mapSizeX][StableData::mapSizeY])
{
    for (int i = 0; i != StableData::mapSizeX; ++i)
	for (int j = 0; j != StableData::mapSizeY; ++j)
	    mapData[i][j] = 0;
}

#endif

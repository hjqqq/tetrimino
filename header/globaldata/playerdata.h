#ifndef PLAYERDATA_H
#define PLAYERDATA_H

#include <vector>

#include "SDL.h"

#include "stabledata.h"
#include "blockdata.h"
#include "vector2.h"
#include "rect.h"

struct PlayerData{
    Uint32 dasDelayTime;

    double horizontalSpeed;
    double normalDropSpeed;
    double softDropSpeed;

    int randomQueueDataIndex;
    enum RandomizerType{BAG, HISTORY4ROLL};
    RandomizerType randomizerType;

    bool ghost;
    bool holder;
    
    Vector2<int> showPixPos;

    SDLKey moveLeft;
    SDLKey moveRight;
    SDLKey rotateLeft;
    SDLKey rotateRight;
    SDLKey softDrop;
    SDLKey hardDrop;
    SDLKey hold;

};

void initPlayerData1();
void initPlayerData2();

#endif

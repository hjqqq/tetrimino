#ifndef GAMEHOLDER_H
#define GAMEHOLDER_H

#include <vector>
#include <algorithm>

#include "stabledata.h"
#include "optiondata.h"
#include "playerdata.h"
#include "randomqueue.h"
#include "game.h"

class GameHolder{
public:
    GameHolder();
    ~GameHolder();
    void handleEvent(const SDL_Event &event);
    void update();
    void initGhostColor();
    
private:
    RandomQueueData* allRandomQueueData[StableData::playerSizeMax];
    Game* allGame[StableData::playerSizeMax];    
};

#endif

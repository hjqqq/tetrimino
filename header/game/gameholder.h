#ifndef GAMEHOLDER_H
#define GAMEHOLDER_H

#include <vector>
#include <algorithm>

#include "stabledata.h"
#include "optiondata.h"
#include "playerdata.h"
#include "randomqueue.h"
#include "quitlabel.h"
#include "game.h"

class GameHolder{
public:
    GameHolder();
    ~GameHolder();
    void handleEvent(const SDL_Event &event);
    void update();

    bool checkAllGameStatus(Game::GameStatus gameStatus);
    void setAllGameStatus(Game::GameStatus gameStatus);
    void setDefenceAttack();
    void setRandomQueue();
    
    void initGhostColor();
private:
    RandomQueueData* allRandomQueueData[StableData::playerSizeMax];
    RandomQueue *allRandomQueue[StableData::playerSizeMax];
    Game* allGame[StableData::playerSizeMax];
    QuitLabel *quitLabel;
    Rect<int> quitLabelRect;
    SDL_Surface *quitLabelBackSurface;
};

#endif

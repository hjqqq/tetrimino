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

/**
   @file gameholder.h
 */

/**
   @brief 处理所有的玩家类（Game 类）。

   负责管理随机数队列，判定游戏整体的状态，如什么时候大家都 Ready，什么时候有人
   胜出，处理整体的暂停功能，并负责显示暂停时的 quitLabel，初始化游戏资源（ghostColor）。
 */
class GameHolder{
public:
    GameHolder();
    ~GameHolder();
    void handleEvent(const SDL_Event &event);
    void update();
private:
    void initGhostColor();
    void initQuitLabel();
    bool checkAllGameStatus(Game::GameStatus gameStatus);
    void setAllGameStatus(Game::GameStatus gameStatus);
    void setRandomQueue();
    
    RandomQueueData* allRandomQueueData[StableData::playerSizeMax];
    RandomQueue *allRandomQueue[StableData::playerSizeMax];
    Game* allGame[StableData::playerSizeMax];
    QuitLabel *quitLabel;
    Rect<int> quitLabelRect;
    SDL_Surface *quitLabelBackSurface;
};

#endif

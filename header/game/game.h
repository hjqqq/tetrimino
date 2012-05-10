#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include <vector>

#include "playerdata.h"
#include "counter.h"
#include "timer.h"
#include "randomqueue.h"
#include "show.h"

class Game{
public:
    Game(PlayerData *_playerData, RandomQueue *randomQueue);
    ~Game();

    void setDefence(Game *game);
    void setAttack(Game *game);
    
    void initTimer();
    void initCounter();
    void initStatus();
    
    void handleEvent(const SDL_Event &event);
    void update();

    void startUpdate();
    void createBlock();

    void areDelayHandleEvent(const SDL_Event &event);
    void areDelayUpdate();
    
    void dropHandleEvent(const SDL_Event &event);
    void dropUpdate();
    bool SRSRotate(Direction startDirection,
		   Direction finishDirection);
    const Vector2<int> findPos(const Vector2<int> &startPos,
			       const Vector2<int> &finishPos,
			       Direction direction);
    bool checkBlock(const Vector2<int> &pos,
		    Direction direction);
    const Vector2<int> getLockPos();
    void fillMap();
    bool checkMapLineFull(int y);
    void checkTSpin();
    void clearMap();
    void addMapGrow(int grow);
    void calGhostPosY();
    
    void lossUpdate();
    void winUpdate();    

private:
    PlayerData *playerData;
    RandomQueue *randomQueue;        
    Show *show;
    
    Game *defence;
    Game *attack;
    
    Timer *dasDelayTimer;
    Timer *areDelayTimer;
    Timer *lockDelayTimer;    

    Counter *horizontalLeftCounter;
    Counter *horizontalRightCounter;
    Counter *normalDropCounter;
    Counter *softDropCounter;

    enum GameStatus{START, AREDELAY, DROP, LOSS, WIN, QUITGAME};    
    GameStatus gameStatus;
    
    int mapData[StableData::mapSizeX][StableData::mapSizeY];
    int mapGrow;
    int series;
    bool backToBack;
    bool tSpin;
    
    enum DropStatus{NORMAL,
		    DASLEFT, ARRLEFT, DASRIGHT, ARRRIGHT};
    DropStatus dropStatus;
    Vector2<int> dropDistancePerFrame;

    bool lockStatus;    

    enum HoldStatus{PREPAREHOLD, HOLD, HOLDED};
    HoldStatus holdStatus;
    bool holdEmpty;
    BlockShape holdShape;    

    Vector2<int> pos;
    BlockShape shape;
    Direction direction;
    
    int ghostPosY[4][StableData::mapSizeX];
};

#endif

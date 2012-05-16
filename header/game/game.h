#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include <vector>

#include "playerdata.h"
#include "counter.h"
#include "timer.h"
#include "randomqueue.h"
#include "show.h"

class GameHolder;

class Game{
public:
    enum GameStatus{PREPARE, READY, START, AREDELAY,
		    DROP, WIN, GAMEOVER, QUITGAME};
    GameStatus gameStatus;    
    Game(PlayerData *_playerData, Game **_allGame);
    ~Game();

    void setRandomQueue(RandomQueue *randomQueue);
    
    void initTimer();
    void initCounter();
    void initStatus();
    
    void handleEvent(const SDL_Event &event);
    void update();

    void prepareHandleEvent(const SDL_Event &event);
    void prepareUpdate();

    void readyUpdate();

    void startUpdate();
    void createBlock();

    void areDelayHandleEvent(const SDL_Event &event);
    void areDelayUpdate();
    void gameOver();
    
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
    GameHolder *gameHolder;
    RandomQueue *randomQueue;

    Game **allGame;
    Show *show;
    
    Timer *dasDelayTimer;
    Timer *areDelayTimer;
    Timer *lockDelayTimer;
    Timer *gameoverDelayTimer;

    Counter *horizontalLeftCounter;
    Counter *horizontalRightCounter;
    Counter *normalDropCounter;
    Counter *softDropCounter;

    bool ready;
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

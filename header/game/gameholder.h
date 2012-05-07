#ifndef GAMEHOLDER_H
#define GAMEHOLDER_H

#include <SDL.h>

#include "counter.h"
#include "timer.h"
#include "mapshow.h"
#include "blockshow.h"
#include "randomqueue.h"

class GameHolder{
public:
    GameHolder();
    ~GameHolder();
    void handleEvent(const SDL_Event &event);
    void update();

    void startUpdate();
    void createBlock();

    void areDelayHandleEvent(const SDL_Event &event);
    void areDelayUpdate();
    
    void dropHandleEvent(const SDL_Event &event);
    void dropUpdate();
    bool SRSRotate(
	BlockData::Direction startDirection,
	BlockData::Direction finishDirection);
    const Vector2<int> findPos(const Vector2<int> &startPos,
			       const Vector2<int> &finishPos,
			       BlockData::Direction direction);
    bool checkBlock(const Vector2<int> &pos,
		    BlockData::Direction direction);
    
    void gameoverUpdate();
    const Vector2<int> getLockPos();
    void fillMap();
    bool checkMapLineFull(int y);
    void clearMap();

    void calGhostPosY();

private:
    Timer *dasDelayTimer;

    Counter *horizontalLeftCounter;
    Counter *horizontalRightCounter;
    Counter *normalDropCounter;
    Counter *softDropCounter;

    Timer *areDelayTimer;
    Timer *lockDelayTimer;
    bool lockStatus;
    
    MapShow *mapShow;
    BlockShow *blockShow;

    enum DropStatus{NORMAL,
		    DASLEFT, ARRLEFT, DASRIGHT, ARRRIGHT};
    DropStatus dropStatus;
    Vector2<int> dropDistancePerFrame;

    enum HoldStatus{PREPAREHOLD, HOLD, HOLDED};
    HoldStatus holdStatus;
    bool holdEmpty;

    int mapGrow;
    
    BlockData::BlockShape holdShape;
    
    RandomQueue *randomQueue;
    int ghostPosY[4][StableData::mapSizeX];
};

#endif

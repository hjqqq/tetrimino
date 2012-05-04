#ifndef GAMEHOLDER_H
#define GAMEHOLDER_H

#include <SDL.h>

#include "counter.h"
#include "timer.h"
#include "mapshow.h"
#include "blockshow.h"

class GameHolder{
public:
    GameHolder();
    ~GameHolder();
    void handleEvent(const SDL_Event &event);
    void update();

    void areDelayUpdate();
    void dropHandleEvent(const SDL_Event &event);
    void dropUpdate();
    void lockDelayUpdate();
    void lockUpdate();

    bool SRSRotate(
	BlockData::Direction startDirection,
	BlockData::Direction finishDirection);
    const Vector2<int> findPos(const Vector2<int> &startPos,
			       const Vector2<int> &finishPos);
    bool checkBlock(const Vector2<int> &pos,
		    BlockData::BlockShape shape,
		    BlockData::Direction direction);

private:
    Timer *dasDelayTimer;
    Timer *arrDelayTimer;
    Counter *normalDropCounter;
    Counter *softDropCounter;
    
    Timer *areDelayTimer;
    Timer *lockDelayTimer;
    
    MapShow *mapShow;
    BlockShow *blockShow;

    enum DropStatus{NORMAL,
		    DASLEFT, ARRLEFT, MOVELEFT,
		    DASRIGHT, ARRRIGHT, MOVERIGHT};
    DropStatus dropStatus;
    Vector2<int> dropDistancePerFrame;
    
    Vector2<int> ghostPos[StableData::mapSizeX];
};

#endif

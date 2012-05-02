#ifndef GAMEHOLDER_H
#define GAMEHOLDER_H

#include <SDL.h>

#include "timer.h"
#include "mapshow.h"
#include "blockshow.h"

class GameHolder{
public:
    GameHolder();
    ~GameHolder();
    void handleEvent(const SDL_Event &event);
    void update();

    void areDelay();
    void drop();
    void lockDelay();
    void lock();
private:
    Timer *dasDelayTimer;
    Timer *areDelayTimer;
    Timer *lockDelayTimer;
    MapShow *mapShow;
    BlockShow *blockShow;
};

#endif

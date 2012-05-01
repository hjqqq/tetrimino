#ifndef GAMEHOLDER_H
#define GAMEHOLDER_H

#include <SDL.h>

#include "mapshow.h"
#include "blockshow.h"

class GameHolder{
public:
    GameHolder();
    ~GameHolder();
    void handleEvent(const SDL_Event &event);
    void update();
    
private:
    MapShow *mapshow;
    BlockShow *blockshow;
};

#endif

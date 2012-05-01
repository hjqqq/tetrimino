#ifndef GAMEHOLDER_H
#define GAMEHOLDER_H

#include <SDL.h>

#include "map.h"

class GameHolder{
public:
    GameHolder();
    ~GameHolder();
    void handleEvent(const SDL_Event &event);
    void update();
    
private:
    Map *map;
};

#endif

#include "playerdata.h"
#include "gameholder.h"

GameHolder::GameHolder()
{
    initPlayerData1();
    mapshow = new MapShow();
    blockshow = new BlockShow();
}

GameHolder::~GameHolder()
{
    delete blockshow;
    delete mapshow;
}

void GameHolder::handleEvent(const SDL_Event &event)
{
    
}

void GameHolder::update()
{
    mapshow->update();
}

#include "playerdata.h"
#include "gameholder.h"

GameHolder::GameHolder()
{
    initPlayerData1();
    map = new Map();
}

GameHolder::~GameHolder()
{
    delete map;
}

void GameHolder::handleEvent(const SDL_Event &event)
{
    
}

void GameHolder::update()
{
    map->update();
}

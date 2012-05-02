#include <iostream>

#include "playerdata.h"
#include "gameholder.h"
#include "optiondata.h"

GameHolder::GameHolder()
{
    initPlayerData1();
    areDelayTimer = new Timer(OptionData::areDelayTime);
    lockDelayTimer = new Timer(OptionData::lockDelayTime);
    mapShow = new MapShow();
    blockShow = new BlockShow();
}

GameHolder::~GameHolder()
{
    delete areDelayTimer;
    delete lockDelayTimer;
    delete blockShow;
    delete mapShow;
}

void GameHolder::handleEvent(const SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN){
	SDLKey sym = event.key.keysym.sym;
	
	if (sym == playerData1.rotateLeft){
	    int direction = playerData1.currentDirection + 1;
	    if (3 < direction)
		direction = 0;
	    playerData1.currentDirection =
		BlockData::Direction(direction);
	}
	
	else if (sym == playerData1.rotateRight){
	    int direction = playerData1.currentDirection - 1;
	    if (direction < 0)
		direction = 3;
	    playerData1.currentDirection =
		BlockData::Direction(direction);
	}
    }
}

void GameHolder::update()
{
    mapShow->update();

    Uint8 *keyState = SDL_GetKeyState(NULL);
    if (keyState[playerData1.moveLeft])
	playerData1.blockPos += Vector2<int>(-1, 0);
    if (keyState[playerData1.moveRight])
	playerData1.blockPos += Vector2<int>(+1, 0);
    
    switch (OptionData::gameHolderStatus){
    case OptionData::AREDELAY:
	areDelay();
	break;
    case OptionData::DROP:
	drop();
	break;
    case OptionData::LOCKDELAY:
	lockDelay();
	break;
    case OptionData::LOCK:
	lock();
	break;
    }
}

void GameHolder::areDelay()
{
    if (areDelayTimer->checkTimeOut())
	OptionData::gameHolderStatus = OptionData::DROP;
}

void GameHolder::drop()
{
    blockShow->update();
    lockDelayTimer->reset();
    //OptionData::gameHolderStatus = OptionData::LOCKDELAY;
}

void GameHolder::lockDelay()
{
    if (lockDelayTimer->checkTimeOut())
	OptionData::gameHolderStatus = OptionData::LOCK;
}

void GameHolder::lock()
{
    areDelayTimer->reset();
    OptionData::gameHolderStatus = OptionData::AREDELAY;
}

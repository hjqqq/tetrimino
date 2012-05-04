#include <cstdlib>
#include <iostream>

#include "playerdata.h"
#include "gameholder.h"
#include "optiondata.h"
#include "wallkickdata.h"

GameHolder::GameHolder()
{
    initPlayerData1();
    dasDelayTimer = new Timer(OptionData::dasDelayTime);
    arrDelayTimer = new Timer(OptionData::arrDelayTime);
    
    if (OptionData::normalDropSpeed < 1){
	normalDropCounter = OptionData::clock->addCounter(
	    1 / OptionData::normalDropSpeed);
    }
    else normalDropCounter = NULL;

    if (OptionData::softDropSpeed < 1)
	softDropCounter = OptionData::clock->addCounter(
	    1 / OptionData::softDropSpeed);
    else softDropCounter = NULL;    
    
    areDelayTimer = new Timer(OptionData::areDelayTime);
    lockDelayTimer = new Timer(OptionData::lockDelayTime);
    
    mapShow = new MapShow();
    blockShow = new BlockShow();

    dropStatus = NORMAL;
    dropDistancePerFrame = Vector2<int>(0, 0);
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
    switch (OptionData::gameHolderStatus){
    case OptionData::DROP:
	dropHandleEvent(event);
	break;
    }
}

void GameHolder::update()
{
    mapShow->update();
    switch (OptionData::gameHolderStatus){
    case OptionData::AREDELAY:
	areDelayUpdate();
	break;
    case OptionData::DROP:
	dropUpdate();
	break;
    case OptionData::LOCKDELAY:
	lockDelayUpdate();
	break;
    case OptionData::LOCK:
	lockUpdate();
	break;
    }
}

void GameHolder::areDelayUpdate()
{
    if (areDelayTimer->checkTimeOut()){
	normalDropCounter->reset();
	OptionData::gameHolderStatus = OptionData::DROP;
    }
}

void GameHolder::dropHandleEvent(const SDL_Event &event)
{
    Uint8 *keyState = SDL_GetKeyState(NULL);
    if (event.type == SDL_KEYUP){
	SDLKey sym = event.key.keysym.sym;
	if (sym == playerData1.moveLeft){
	    if (keyState[playerData1.moveRight])
		dropStatus = ARRRIGHT;
	    else
		dropStatus = NORMAL;
	}
	else if (sym == playerData1.moveRight){
	    if (keyState[playerData1.moveLeft])
		dropStatus = ARRLEFT;
	    else
		dropStatus = NORMAL;
	}
    }
    
    if (event.type == SDL_KEYDOWN){
	SDLKey sym = event.key.keysym.sym;
	if (sym == playerData1.moveLeft){
	    dropDistancePerFrame += Vector2<int>(-1, 0);
	    if (keyState[playerData1.moveRight])
		dropStatus = ARRLEFT;
	    else{
		dropStatus = DASLEFT;
		dasDelayTimer->reset();
	    }
	}

	else if (sym == playerData1.moveRight){
	    dropDistancePerFrame += Vector2<int>(1, 0);
	    if (keyState[playerData1.moveLeft])
		dropStatus = ARRRIGHT;
	    else {
		dropStatus = DASRIGHT;
		dasDelayTimer->reset();
	    }
	}
	
	else if (sym == playerData1.rotateLeft){
	    int direction = playerData1.currentDirection + 1;
	    if (3 < direction)
		direction = 0;
	    SRSRotate(playerData1.currentDirection,
		      (BlockData::Direction)direction);
	}
	
	else if (sym == playerData1.rotateRight){
	    int direction = playerData1.currentDirection - 1;
	    if (direction < 0)
		direction = 3;
	    SRSRotate(playerData1.currentDirection,
		      (BlockData::Direction)direction);	    
	}

	else if (sym == SDLK_SPACE){
	    playerData1.currentBlockShape = BlockData::BlockShape((playerData1.currentBlockShape + 1) % 7);
	    playerData1.blockPos = blockStartPosArray[playerData1.currentBlockShape];	
	}
    }    
}

void GameHolder::dropUpdate()
{
    switch (dropStatus){
    case NORMAL:
	break;
    case DASLEFT:
	if (dasDelayTimer->checkTimeOut()){
	    arrDelayTimer->reset();
	    dropStatus = ARRLEFT;
	}	
	break;
    case ARRLEFT:
	if (arrDelayTimer->checkTimeOut()){
	    dropStatus = MOVELEFT;
	}
	break;
    case MOVELEFT:
	arrDelayTimer->reset();
	dropDistancePerFrame += Vector2<int>(-1, 0);
	dropStatus = ARRLEFT;
	break;
	
    case DASRIGHT:
	if (dasDelayTimer->checkTimeOut()){
	    arrDelayTimer->reset();
	    dropStatus = ARRRIGHT;
	}	
	break;
    case ARRRIGHT:
	if (arrDelayTimer->checkTimeOut()){
	    dropStatus = MOVERIGHT;
	}	
	break;
    case MOVERIGHT:
	arrDelayTimer->reset();
	dropDistancePerFrame += Vector2<int>(1, 0);
	dropStatus = ARRRIGHT;	
	break;
    }

    Uint8 *keyState = SDL_GetKeyState(NULL);

    if (keyState[playerData1.softDrop]){
	if (softDropCounter == NULL)
	    dropDistancePerFrame += Vector2<int>(
		0, (int)OptionData::softDropSpeed);
	else {
	    if (!softDropCounter->getRemain()){
		dropDistancePerFrame += Vector2<int>(0, 1);
		softDropCounter->reset();
	    }
	}
    }

    if (normalDropCounter == NULL)
	dropDistancePerFrame += Vector2<int>(
	    0, (int)OptionData::normalDropSpeed);
    else {
	if (!normalDropCounter->getRemain()){
	    dropDistancePerFrame += Vector2<int>(0, 1);
	    normalDropCounter->reset();
	}
    }

    playerData1.blockPos = findPos(
	playerData1.blockPos, playerData1.blockPos + dropDistancePerFrame);
    dropDistancePerFrame = Vector2<int>(0, 0);

    blockShow->update();
    
    lockDelayTimer->reset();
    //OptionData::gameHolderStatus = OptionData::LOCKDELAY;
}

void GameHolder::lockDelayUpdate()
{
    if (lockDelayTimer->checkTimeOut())
	OptionData::gameHolderStatus = OptionData::LOCK;
}

void GameHolder::lockUpdate()
{
    areDelayTimer->reset();
    playerData1.blockPos = blockStartPosArray[playerData1.currentBlockShape];
    OptionData::gameHolderStatus = OptionData::AREDELAY;
}

bool GameHolder::SRSRotate(
    BlockData::Direction startDirection,
    BlockData::Direction finishDirection)
{
    const WallKickData &wallKickData =
	wallKickDataArray[playerData1.currentBlockShape];
    const WallKickData::WallKickNum &wallKickNum =
	wallKickData.getNum(startDirection, finishDirection);

    Vector2<int> testPos = playerData1.blockPos;
    
    for (int i = 0; i != 5; ++i){
	testPos = playerData1.blockPos + wallKickNum[i];
	if (checkBlock(testPos,
		       playerData1.currentBlockShape,
		       finishDirection)){
	    playerData1.blockPos = testPos;
	    playerData1.currentDirection = finishDirection;
	    return true;
	}
    }
    return false;
}

const Vector2<int> GameHolder::findPos(
    const Vector2<int> &startPos,
    const Vector2<int> &finishPos)
{
    Vector2<int> result = startPos;
    Vector2<int> testPos = startPos;
    Vector2<int> distance = finishPos - testPos;
    while (testPos != finishPos){
	if (distance.x < 0){
	    if (-distance.x <= distance.y)
		testPos.y += 1;
	    else
		testPos.x -= 1;
	} else{
	    if (distance.x <= distance.y)
		testPos.y += 1;
	    else
		testPos.x += 1;
	}
	if (checkBlock(testPos,
		       playerData1.currentBlockShape,
		       playerData1.currentDirection)){
	    result = testPos;
	} else {
	    break;
	}
	distance  = finishPos - testPos;
    }
    return result;
}

bool GameHolder::checkBlock(
    const Vector2<int> &pos,
    BlockData::BlockShape shape,
    BlockData::Direction direction)
{
    const BlockData &blockData = blockDataArray[shape];

    const BlockData::BlockNum &blockNum = blockData.getNum(direction);

    const Rect<int> &origBlockRect = blockData.getRect(direction);
    const Vector2<int> origBlockRectTopLeft = origBlockRect.getTopLeft();
    const Vector2<int> origBlockRectBottomRight = origBlockRect.getBottomRight();
    
    Rect<int> blockRect = origBlockRect;
    blockRect.move(pos);
    const Vector2<int> blockRectTopLeft = blockRect.getTopLeft();
    const Vector2<int> blockRectBottomRight = blockRect.getBottomRight();
	
    for (int j = blockRectBottomRight.y - 1, origJ = origBlockRectBottomRight.y - 1;
	 j >= blockRectTopLeft.y && j >= 0;
	 --j, --origJ){
	
	for (int i = blockRectTopLeft.x, origI = origBlockRectTopLeft.x;
	     i != blockRectBottomRight.x;
	     ++i, ++origI){
	    
	    if (i < 0 || StableData::mapSize.x <= i ||
		StableData::mapSize.y <= j ||
		(blockNum[origI][origJ] == 1 &&
		 playerData1.mapData[i][j] == 1))
		return false;
	    
	}
    }
    return true;
}

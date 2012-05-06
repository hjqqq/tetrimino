#include <cstdlib>
#include <iostream>

#include "playerdata.h"
#include "gameholder.h"
#include "optiondata.h"
#include "wallkickdata.h"
#include "randomqueue.h"

GameHolder::GameHolder()
{
    initPlayerData1();
    dasDelayTimer = new Timer(OptionData::dasDelayTime);

    if (OptionData::horizontalSpeed < 1){
	horizontalLeftCounter = OptionData::clock->addCounter(
	    1 / OptionData::horizontalSpeed);
	horizontalRightCounter = OptionData::clock->addCounter(
	    1 / OptionData::horizontalSpeed);
    } else horizontalLeftCounter = horizontalRightCounter = NULL;
    
    if (OptionData::normalDropSpeed < 1){
	normalDropCounter = OptionData::clock->addCounter(
	    1 / OptionData::normalDropSpeed);
    } else normalDropCounter = NULL;

    if (OptionData::softDropSpeed < 1){
	softDropCounter = OptionData::clock->addCounter(
	    1 / OptionData::softDropSpeed);
    } else softDropCounter = NULL;    
    
    areDelayTimer = new Timer(OptionData::areDelayTime);
    lockDelayTimer = new Timer(OptionData::lockDelayTime);
    lockStatus = false;
    
    mapShow = new MapShow();
    blockShow = new BlockShow();

    dropStatus = NORMAL;
    dropDistancePerFrame = Vector2<int>(0, 0);

    switch (OptionData::randomizerType){
    case OptionData::BAG:
	randomQueue = new RandomQueue(new BagRandomizer());
	break;
    case OptionData::HISTORY4ROLL:
	randomQueue = new RandomQueue(
	    new HistoryRollRandomizer<4>(OptionData::history4Roll));
	break;
    }
}

GameHolder::~GameHolder()
{
    delete randomQueue;
    delete blockShow;    
    delete mapShow;    
    delete lockDelayTimer;
    delete areDelayTimer;
}

void GameHolder::handleEvent(const SDL_Event &event)
{
    switch (OptionData::gameHolderStatus){
    case OptionData::START: case OptionData::AREDELAY:
	areDelayHandleEvent(event);
	break;
    case OptionData::DROP:
	dropHandleEvent(event);
	break;
    }
}

void GameHolder::update()
{
    static int count = 0;
    mapShow->update();
    switch (OptionData::gameHolderStatus){
    case OptionData::START:
	startUpdate();
    case OptionData::AREDELAY:
	areDelayUpdate();
	break;
    case OptionData::DROP:
	dropUpdate();
	break;
    case OptionData::GAMEOVER:
	gameoverUpdate();
	break;
    }
}

void GameHolder::startUpdate()
{
    areDelayTimer->reset();
    
    clearMap();
    
    playerData1.currentBlockShape = BlockData::BlockShape(*randomQueue->begin());
    randomQueue->pop();
    
    playerData1.blockPos = blockStartPosArray[playerData1.currentBlockShape];
    calGhostPosY();
    
    OptionData::gameHolderStatus = OptionData::AREDELAY;
}

void GameHolder::areDelayHandleEvent(const SDL_Event &event)
{
    if (event.type == SDL_KEYUP){
	SDLKey sym = event.key.keysym.sym;
	if (sym == playerData1.moveLeft){
	    dropStatus = NORMAL;
	}
	else if (sym == playerData1.moveRight){
	    dropStatus = NORMAL;
	}
    }
    
    if (event.type == SDL_KEYDOWN){
	SDLKey sym = event.key.keysym.sym;
	if (sym == playerData1.moveLeft){
	    dropStatus = ARRLEFT;
	}
	else if (sym == playerData1.moveRight){
	    dropStatus = ARRRIGHT;
	}
	else if (sym == playerData1.rotateLeft){
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

void GameHolder::areDelayUpdate()
{
    if (areDelayTimer->checkTimeOut()){
	normalDropCounter->reset();
	if (!checkBlock(playerData1.blockPos,
			playerData1.currentDirection)){
	    OptionData::gameHolderStatus = OptionData::GAMEOVER;
	} else
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

	else if (sym == playerData1.hardDrop){
	    playerData1.blockPos = getLockPos();
	    fillMap();
	    OptionData::gameHolderStatus = OptionData::START;
	}

	else if (sym == SDLK_SPACE){
	    cleanMapData(playerData1.mapData);
	    OptionData::gameHolderStatus = OptionData::START;
	}

	if (lockStatus)
	    lockDelayTimer->reset();
    }    
}

void GameHolder::dropUpdate()
{
    switch (dropStatus){
    case NORMAL:
	break;
    case DASLEFT:
	if (dasDelayTimer->checkTimeOut()){
	    dropStatus = ARRLEFT;
	}	
	break;
    case ARRLEFT:
	if (horizontalLeftCounter == NULL){
	    dropDistancePerFrame += Vector2<int>(-OptionData::horizontalSpeed, 0);
	}
	else if (!horizontalLeftCounter->getRemain()){
	    dropDistancePerFrame += Vector2<int>(-1, 0);
	    horizontalLeftCounter->reset();
	}
	break;

    case DASRIGHT:
	if (dasDelayTimer->checkTimeOut()){
	    dropStatus = ARRRIGHT;
	}	
	break;
    case ARRRIGHT:
	if (horizontalRightCounter == NULL)
	    dropDistancePerFrame += Vector2<int>(OptionData::horizontalSpeed, 0);
	else if (!horizontalRightCounter->getRemain()){
	    dropDistancePerFrame += Vector2<int>(1, 0);
	    horizontalRightCounter->reset();
	}
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
	playerData1.blockPos,
	playerData1.blockPos + dropDistancePerFrame,
	playerData1.currentDirection);

    dropDistancePerFrame = Vector2<int>(0, 0);

    if (playerData1.blockPos == getLockPos()){
	if (!lockStatus){
	    lockStatus = true;
	    lockDelayTimer->reset();
	}
    }else {
	lockStatus = false;	
    }

    if (lockStatus && lockDelayTimer->checkTimeOut()){
	lockStatus = false;
	fillMap();
	OptionData::gameHolderStatus = OptionData::START;
    }

    blockShow->update();
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
	if (checkBlock(testPos, finishDirection)){
	    playerData1.blockPos = testPos;
	    playerData1.currentDirection = finishDirection;
	    return true;
	}
    }
    return false;
}

const Vector2<int> GameHolder::findPos(
    const Vector2<int> &startPos,
    const Vector2<int> &finishPos,
    BlockData::Direction direction)
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
	if (checkBlock(testPos, direction)){
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
    BlockData::Direction direction)
{
    const BlockData &blockData = blockDataArray[playerData1.currentBlockShape];

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

void GameHolder::gameoverUpdate()
{
    static int counter = 0;
    std::cerr << "gameover !!!\n";
}

const Vector2<int> GameHolder::getLockPos()
{
    const BlockData &blockData =
	blockDataArray[playerData1.currentBlockShape];
    const Rect<int> &blockRect =
	blockData.getRect(playerData1.currentDirection);
    
    int ghostIndex = playerData1.blockPos.x + blockRect.getTopLeft().x;
    
    int &currentGhostPosY = ghostPosY[playerData1.currentDirection][ghostIndex];

    if (currentGhostPosY < playerData1.blockPos.y){
	currentGhostPosY =
	    findPos(playerData1.blockPos,
		    Vector2<int>(playerData1.blockPos.x, StableData::mapSize.y),
		    playerData1.currentDirection).y;
    }
    return Vector2<int>(playerData1.blockPos.x, currentGhostPosY);
}

void GameHolder::fillMap()
{
    const BlockData &blockData = blockDataArray[playerData1.currentBlockShape];

    const BlockData::BlockNum &blockNum = blockData.getNum(playerData1.currentDirection);

    const Rect<int> &origBlockRect = blockData.getRect(playerData1.currentDirection);
    const Vector2<int> origBlockRectTopLeft = origBlockRect.getTopLeft();
    const Vector2<int> origBlockRectBottomRight = origBlockRect.getBottomRight();
    
    Rect<int> blockRect = origBlockRect;
    blockRect.move(playerData1.blockPos);
    const Vector2<int> blockRectTopLeft = blockRect.getTopLeft();
    const Vector2<int> blockRectBottomRight = blockRect.getBottomRight();
	
    for (int j = blockRectBottomRight.y - 1, origJ = origBlockRectBottomRight.y - 1;
	 j >= blockRectTopLeft.y && j >= 0;
	 --j, --origJ){
	
	for (int i = blockRectTopLeft.x, origI = origBlockRectTopLeft.x;
	     i != blockRectBottomRight.x;
	     ++i, ++origI){
	    if (blockNum[origI][origJ] == 1)
		playerData1.mapData[i][j] = blockNum[origI][origJ];
	}
    }    
}

void GameHolder::clearMap()
{
    int origY = StableData::mapSize.y - 1,
	destY = origY;
    while (origY >= 0){
	if (!checkMapLineFull(origY)){
	    for (int i = 0; i != StableData::mapSize.x; ++i){
		playerData1.mapData[i][destY] =
		    playerData1.mapData[i][origY];
	    }
	    --destY;
	} 
	--origY;
    }
}

bool GameHolder::checkMapLineFull(int y)
{
    for (int i = 0; i != StableData::mapSize.x; ++i)
	if (playerData1.mapData[i][y] != 1)
	    return false;
    return true;
}

void GameHolder::calGhostPosY()
{
    const BlockData &blockData =
	blockDataArray[playerData1.currentBlockShape];

    for (int direction = 0; direction != 4; ++direction){
	const BlockData::BlockNum &blockNum =
	    blockData.getNum(BlockData::Direction(direction));

	const Rect<int> &blockRect =
	    blockData.getRect(BlockData::Direction(direction));

	const Vector2<int> blockRectTopLeft = blockRect.getTopLeft();
	const Vector2<int> blockRectBottomRight = blockRect.getBottomRight();

	for (int i = -blockRectTopLeft.x;
	     i <= StableData::mapSize.x - blockRectBottomRight.x;
	     ++i){
	    ghostPosY[direction][i + blockRectTopLeft.x] =
		findPos(Vector2<int>(i, -4),
			Vector2<int>(i, StableData::mapSize.y),
		        BlockData::Direction(direction)).y;
	}
    }
}

#include <cstdlib>
#include <iostream>

#include "utility.h"
#include "playerdata.h"
#include "game.h"
#include "optiondata.h"
#include "resourcedata.h"
#include "wallkickdata.h"
#include "randomqueue.h"

Game::Game(PlayerData *_playerData):
    playerData(_playerData),
    show(new Show(_playerData))
{
    initTimer();
    initCounter();
    initStatus();
    gameStatus = PREPARE;
    defence = attack = this;
}

Game::~Game()
{
    delete show;
    delete lockDelayTimer;
    delete areDelayTimer;
    delete dasDelayTimer;
}

void Game::setDefence(Game *game)
{
    defence = game;
}

void Game::setAttack(Game *game)
{
    attack = game;
}

void Game::setRandomQueue(RandomQueue *randomQueue)
{
    this->randomQueue = randomQueue;
}

void Game::initTimer()
{
    dasDelayTimer = new Timer(playerData->dasDelayTime);
    areDelayTimer = new Timer(OptionData::areDelayTime);
    lockDelayTimer = new Timer(OptionData::lockDelayTime);
    gameoverDelayTimer = new Timer(2000);
}

void Game::initCounter()
{
    if (playerData->horizontalSpeed < 1){
	horizontalLeftCounter = ResourceData::clock->addCounter(
	    1 / playerData->horizontalSpeed);
	horizontalRightCounter = ResourceData::clock->addCounter(
	    1 / playerData->horizontalSpeed);
    } else{
	horizontalLeftCounter = horizontalRightCounter = NULL;
    }
    
    if (playerData->normalDropSpeed < 1){
	normalDropCounter = ResourceData::clock->addCounter(
	    1 / playerData->normalDropSpeed);
    } else{
	normalDropCounter = NULL;
    }

    if (playerData->softDropSpeed < 1){
	softDropCounter = ResourceData::clock->addCounter(
	    1 / playerData->softDropSpeed);
    } else{
	softDropCounter = NULL;
    }
}

void Game::initStatus()
{
    for (int j = 0; j != StableData::mapSizeY; ++j)
	for (int i = 0; i != StableData::mapSizeX; ++i)
	    mapData[i][j] = BACKCOLOR;
    
    mapGrow = 0;
    series = 0;
    backToBack = false;
    tSpin = false;
    
    dropStatus = NORMAL;
    dropDistancePerFrame = Vector2<int>(0, 0);

    lockStatus = false;

    holdStatus = PREPAREHOLD;
    holdEmpty = true;
}

void Game::handleEvent(const SDL_Event &event)
{
    switch (gameStatus){
    case PREPARE:
	prepareHandleEvent(event);
	break;
    case START: case AREDELAY:
	areDelayHandleEvent(event);
	break;
    case DROP:
	dropHandleEvent(event);
	break;
    }
}

void Game::update()
{
    switch (gameStatus){
    case PREPARE:
	prepareUpdate();
	break;
    case START:
	startUpdate();
	break;
    case AREDELAY:
	areDelayUpdate();
	break;
    case DROP:
	dropUpdate();
	break;
    case WIN:
	winUpdate();
	break;
    }
}

void Game::prepareHandleEvent(const SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN){
	SDLKey sym = event.key.keysym.sym;
	if (sym == playerData->moveLeft ||
	    sym == playerData->moveRight ||
	    sym == playerData->rotateLeft ||
	    sym == playerData->rotateRight ||
	    sym == playerData->hardDrop ||
	    sym == playerData->hold){
	    
	    initStatus();
	    show->mapShow(mapData);
	    show->messageShow("Ready !!!");
	    gameStatus = READY;
	}
    }    
}

void Game::prepareUpdate()
{
    show->mapShow(mapData);
    show->messageShow("Ready ???");
}

void Game::startUpdate()
{
    areDelayTimer->reset();
    
    clearMap();
    show->mapShow(mapData);
    
    createBlock();
    show->previewShow(randomQueue->begin(), randomQueue->begin() + 4);
    
    calGhostPosY();
    show->ghostShow(getLockPos(),
		    shape,
		    direction);
    
    gameStatus = AREDELAY;
}

void Game::createBlock()
{
    switch (holdStatus){
        case PREPAREHOLD:
	    shape = BlockShape(*randomQueue->begin());
	    randomQueue->pop();
	    break;
	case HOLD:
	    if (holdEmpty){
		holdShape = shape;
		shape = BlockShape(*randomQueue->begin());
		randomQueue->pop();
		holdStatus = HOLDED;
		holdEmpty = false;
		show->holdShow(holdShape);		
	    } else{
		std::swap(shape, holdShape);
		holdStatus = HOLDED;
		show->holdShow(holdShape);
	    }
	    break;
	case HOLDED:
	    shape = BlockShape(*randomQueue->begin());
	    randomQueue->pop();	    
	    holdStatus = PREPAREHOLD;
	    break;
    }
    pos = blockStartPosArray[shape];
    direction = NORTH;
}

void Game::areDelayHandleEvent(const SDL_Event &event)
{
    if (event.type == SDL_KEYUP){
	SDLKey sym = event.key.keysym.sym;
	if (sym == playerData->moveLeft){
	    dropStatus = NORMAL;
	}
	else if (sym == playerData->moveRight){
	    dropStatus = NORMAL;
	}
    }
    
    if (event.type == SDL_KEYDOWN){
	SDLKey sym = event.key.keysym.sym;
	if (sym == playerData->moveLeft){
	    dropStatus = ARRLEFT;
	}
	else if (sym == playerData->moveRight){
	    dropStatus = ARRRIGHT;
	}
	else if (sym == playerData->rotateLeft){
	    direction = Direction(
		direction == 3? 0: direction + 1);
	}
	else if (sym == playerData->rotateRight){
	    direction = Direction(
		direction == 0? 3: direction - 1);
	}
	else if (sym == playerData->hardDrop){
	    pos = getLockPos();
	    if (!checkBlock(pos, direction))
		gameOver();
	    else{
		fillMap();
		gameStatus = START;
	    }
	}
	else if (sym == playerData->hold){
	    if (holdStatus == PREPAREHOLD){
		holdStatus = HOLD;
		gameStatus = START;
	    }
	}
    }
}

void Game::areDelayUpdate()
{
    show->mapShow(mapData);
    show->ghostShow(getLockPos(),
		    shape,
		    direction);
    if (areDelayTimer->checkTimeOut()){
	if (!checkBlock(pos, direction)){
	    gameOver();
	} else{
	    if (normalDropCounter != NULL)
		normalDropCounter->reset();	    
	    gameStatus = DROP;
	}
    }
}

void Game::gameOver()
{
    defence->attack = attack;
    attack->defence = defence;
    if (defence == attack){
	defence->gameStatus = WIN;
	defence->show->messageShow("Win !!!");
	defence->gameoverDelayTimer->reset();
    }
    gameStatus = GAMEOVER;
    show->messageShow("Loss !!!");
}

void Game::dropHandleEvent(const SDL_Event &event)
{
    Uint8 *keyState = SDL_GetKeyState(NULL);
    if (event.type == SDL_KEYUP){
	SDLKey sym = event.key.keysym.sym;
	if (sym == playerData->moveLeft){
	    if (keyState[playerData->moveRight])
		dropStatus = ARRRIGHT;
	    else
		dropStatus = NORMAL;
	}
	else if (sym == playerData->moveRight){
	    if (keyState[playerData->moveLeft])
		dropStatus = ARRLEFT;
	    else
		dropStatus = NORMAL;
	}
    }
    
    if (event.type == SDL_KEYDOWN){
	SDLKey sym = event.key.keysym.sym;
	if (sym == playerData->moveLeft){
	    dropDistancePerFrame += Vector2<int>(-1, 0);
	    if (keyState[playerData->moveRight])
		dropStatus = ARRLEFT;
	    else{
		dropStatus = DASLEFT;
		dasDelayTimer->reset();
	    }
	}

	else if (sym == playerData->moveRight){
	    dropDistancePerFrame += Vector2<int>(1, 0);
	    if (keyState[playerData->moveLeft])
		dropStatus = ARRRIGHT;
	    else {
		dropStatus = DASRIGHT;
		dasDelayTimer->reset();
	    }
	}
	
	else if (sym == playerData->rotateLeft){
	    int newDirection = (direction == 3? 0: direction + 1);
	    if (SRSRotate(direction, (Direction)newDirection) &&
		lockStatus){
		lockDelayTimer->reset();
	    }
	}
	
	else if (sym == playerData->rotateRight){
	    int newDirection = (direction == 0? 3: direction - 1);
	    if (SRSRotate(direction, (Direction)newDirection) &&
		lockStatus){
		lockDelayTimer->reset();
	    }
	}

	else if (sym == playerData->hardDrop){
	    lockStatus = false;
	    pos = getLockPos();
	    fillMap();
	    gameStatus = START;
	}

	else if (sym == playerData->hold){
	    if (holdStatus == PREPAREHOLD){
		holdStatus = HOLD;
		gameStatus = START;
	    }
	}
    }    
}

void Game::dropUpdate()
{
    show->mapShow(mapData);
    show->ghostShow(getLockPos(), shape, direction);
    show->dropBlockShow(pos, shape, direction);    
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
	    dropDistancePerFrame += Vector2<int>(-playerData->horizontalSpeed, 0);
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
	    dropDistancePerFrame += Vector2<int>(playerData->horizontalSpeed, 0);
	else if (!horizontalRightCounter->getRemain()){
	    dropDistancePerFrame += Vector2<int>(1, 0);
	    horizontalRightCounter->reset();
	}
	break;
    }

    Uint8 *keyState = SDL_GetKeyState(NULL);

    if (!lockStatus){
	if (keyState[playerData->softDrop]){
	    if (softDropCounter == NULL)
		dropDistancePerFrame += Vector2<int>(
		    0, (int)playerData->softDropSpeed);
	    else {
		if (!softDropCounter->getRemain()){
		    dropDistancePerFrame += Vector2<int>(0, 1);
		    softDropCounter->reset();
		}
	    }
	}
	if (normalDropCounter == NULL)
	    dropDistancePerFrame += Vector2<int>(
		0, (int)playerData->normalDropSpeed);
	else {
	    if (!normalDropCounter->getRemain()){
		dropDistancePerFrame += Vector2<int>(0, 1);
		normalDropCounter->reset();
	    }
	}
    }

    Vector2<int> newPos = findPos(pos, pos + dropDistancePerFrame, direction);
    if (pos != newPos && lockStatus){
	lockDelayTimer->reset();
    }
    pos = newPos;	    
    dropDistancePerFrame = Vector2<int>(0, 0);

    if (pos == getLockPos()){
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
	gameStatus = START;
    }

}

bool Game::SRSRotate(Direction startDirection,
		     Direction finishDirection)
{
    const WallKickData &wallKickData = wallKickDataArray[shape];
    const WallKickData::WallKickNum &wallKickNum =
	wallKickData.getNum(startDirection, finishDirection);

    Vector2<int> testPos = pos;
    
    for (int i = 0; i != 5; ++i){
	testPos = pos + wallKickNum[i];
	if (checkBlock(testPos, finishDirection)){
	    pos = testPos;
	    direction = finishDirection;
	    return true;
	}
    }
    return false;
}

const Vector2<int> Game::findPos(const Vector2<int> &startPos,
				 const Vector2<int> &finishPos,
				 Direction direction)
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

bool Game::checkBlock(const Vector2<int> &pos,
		      Direction direction)
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
		(blockNum[origI][origJ] != EMPTY &&
		 mapData[i][j] != BACKCOLOR))
		return false;
	}
    }
    return true;
}

const Vector2<int> Game::getLockPos()
{
    const BlockData &blockData = blockDataArray[shape];
    const Rect<int> &blockRect = blockData.getRect(direction);
    
    int ghostIndex = pos.x + blockRect.getTopLeft().x;
    
    int &currentGhostPosY = ghostPosY[direction][ghostIndex];

    if (currentGhostPosY < pos.y){
	currentGhostPosY =
	    findPos(pos,
		    Vector2<int>(pos.x, StableData::mapSize.y),
		    direction).y;
    }
    return Vector2<int>(pos.x, currentGhostPosY);
}

void Game::fillMap()
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
	    if (blockNum[origI][origJ] != EMPTY)
		mapData[i][j] = blockNum[origI][origJ];
	}
    }

    if (shape == TSHAPE &&
	((direction == NORTH && pos.y < StableData::mapSize.y - 3) ||
	 (direction == WEST && pos.x < StableData::mapSize.x - 3) ||
	 (direction == SOUTH && 2 <= pos.y) ||
	 (direction == EAST && 2 <= pos.x)) &&
	-1 <= pos.y && 
	(bool)(mapData[pos.x + 1][pos.y + 1] - BACKCOLOR) +
	(bool)(mapData[pos.x + 3][pos.y + 1] - BACKCOLOR) +
	(bool)(mapData[pos.x + 1][pos.y + 3] - BACKCOLOR) +
	(bool)(mapData[pos.x + 3][pos.y + 3] - BACKCOLOR)== 3){
	tSpin = true;
    } else{
	backToBack = false;
	tSpin = false;
    }    
}

void Game::clearMap()
{
    int origY = StableData::mapSize.y - 1,
	destY = origY;

    while (origY >= 0){
	if (!checkMapLineFull(origY)){
	    for (int i = 0; i != StableData::mapSize.x; ++i){
		mapData[i][destY] = mapData[i][origY];
	    }
	    --destY;
	}
	--origY;
    }

    if (this != attack){
	addMapGrow(destY + 1);
    }

    while (destY >= 0){
	for (int i = 0; i != StableData::mapSize.x; ++i)
	    mapData[i][destY] = BACKCOLOR;
	--destY;
    }
    
    if (mapGrow != 0){
	for (int j = 0; j != StableData::mapSize.y - mapGrow; ++j){
	    for (int i = 0; i != StableData::mapSize.x; ++i)
		mapData[i][j] = mapData[i][j + mapGrow];
	}
    
	int hole = randInt(0, StableData::mapSize.x);
    
	for (int j = StableData::mapSize.y - mapGrow; j != StableData::mapSize.y; ++j){
	    for (int i = 0; i != StableData::mapSize.x; ++i){
		if (i == hole)
		    mapData[i][j] = BACKCOLOR;
		else
		    mapData[i][j] = GARBAGECOLOR;
	    }
	}
    }
    mapGrow = 0;
    show->growBarShow(mapGrow);    
}

void Game::addMapGrow(int grow)
{
    if (backToBack){
	if (tSpin){
	    switch (grow){
	    case 1:
		grow = 2;
		break;
	    case 2:
		grow = 4;
		break;
	    case 3:
		grow = 6;
		break;
	    }
	}
	if (grow == 4){
	    grow = 5;
	}
    }else{
	if (tSpin){
	    backToBack = true;
	    switch (grow){
	    case 1:
		grow = 3;
		break;
	    case 2:
		grow = 5;
		break;
	    case 3:
		grow = 8;
		break;
	    }
	}
	if (grow == 4)
	    backToBack = true;
	else{
	    backToBack = false;
	    if (grow != 0)
		--grow;
	}
    }
    if (mapGrow >= grow)
	mapGrow -= grow;
    else{
	grow -= mapGrow;
	mapGrow = 0;
	attack->mapGrow += grow;
	attack->show->growBarShow(attack->mapGrow);
    }
}

bool Game::checkMapLineFull(int y)
{
    for (int i = 0; i != StableData::mapSize.x; ++i)
	if (mapData[i][y] == BACKCOLOR)
	    return false;
    return true;
}

void Game::calGhostPosY()
{
    const BlockData &blockData = blockDataArray[shape];

    for (int direction = 0; direction != 4; ++direction){
	const BlockData::BlockNum &blockNum =
	    blockData.getNum(Direction(direction));

	const Rect<int> &blockRect =
	    blockData.getRect(Direction(direction));

	const Vector2<int> blockRectTopLeft = blockRect.getTopLeft();
	const Vector2<int> blockRectBottomRight = blockRect.getBottomRight();

	for (int i = -blockRectTopLeft.x;
	     i <= StableData::mapSize.x - blockRectBottomRight.x;
	     ++i){
	    ghostPosY[direction][i + blockRectTopLeft.x] =
		findPos(Vector2<int>(i, -4),
			Vector2<int>(i, StableData::mapSize.y),
		        Direction(direction)).y;
	}
    }
}

void Game::winUpdate()
{
    if (gameoverDelayTimer->checkTimeOut()){
	gameStatus = GAMEOVER;
    }
}

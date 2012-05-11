#include "gameholder.h"

GameHolder::GameHolder()
{
    initGhostColor();
    SDL_BlitSurface(ResourceData::background, 0,
		    ResourceData::display, 0);
    
    for (int i = 0; i != StableData::playerSizeMax; ++i){
	allGame[i] = NULL;	
	allRandomQueueData[i] = NULL;
	allRandomQueue[i] = NULL;
    }

    for (int i = 0; i != OptionData::playerSize; ++i){
	allGame[i] = new Game(OptionData::allPlayerData[i]);
    }
    
    setDefenceAttack();
    setRandomQueue();
    setAllGameStatus(Game::PREPARE);
    OptionData::gameHolderStatus = OptionData::READY;
}

GameHolder::~GameHolder()
{
    for (int i = 0; i != StableData::playerSizeMax; ++i){
	delete allGame[i];
	delete allRandomQueueData[i];
	delete allRandomQueue[i];
    }
}

void GameHolder::handleEvent(const SDL_Event &event)
{
    switch (OptionData::gameHolderStatus){
    case OptionData::READY:
	for (int i = 0; i != OptionData::playerSize; ++i){
	    allGame[i]->handleEvent(event);
	}
	break;
    case OptionData::RUN:
	if (event.type == SDL_KEYDOWN){
	    SDLKey sym = event.key.keysym.sym;
	    if (sym == SDLK_ESCAPE){
		OptionData::gameHolderStatus = OptionData::PAUSE;
	    }
	}
	for (int i = 0; i != OptionData::playerSize; ++i){
	    allGame[i]->handleEvent(event);
	}
	break;
    case OptionData::PAUSE:
	if (event.type == SDL_KEYDOWN){
	    SDLKey sym = event.key.keysym.sym;
	    if (sym == SDLK_ESCAPE){
		OptionData::gameHolderStatus = OptionData::RUN;
	    }
	}
	break;
    }
}

void GameHolder::update()
{
    switch(OptionData::gameHolderStatus){
    case OptionData::READY:
	if (checkAllGameStatus(Game::READY)){
	    setAllGameStatus(Game::START);
	    OptionData::gameHolderStatus = OptionData::RUN;	    
	}
	for (int i = 0; i != OptionData::playerSize; ++i){
	    allGame[i]->update();
	}
	break;
    case OptionData::RUN:
	if (checkAllGameStatus(Game::GAMEOVER)){
	    setDefenceAttack();
	    setRandomQueue();
	    setAllGameStatus(Game::PREPARE);
	    OptionData::gameHolderStatus = OptionData::READY;
	}
	for (int i = 0; i != OptionData::playerSize; ++i){
	    allGame[i]->update();
	}	
	break;
    case OptionData::PAUSE:
	break;
    }

}

bool GameHolder::checkAllGameStatus(Game::GameStatus gameStatus)
{
    for (int i = 0; i != OptionData::playerSize; ++i)
	if (allGame[i]->gameStatus != gameStatus)
	    return false;
    return true;    
}

void GameHolder::setAllGameStatus(Game::GameStatus gameStatus)
{
    for (int i = 0; i != OptionData::playerSize; ++i)
	allGame[i]->gameStatus = gameStatus;
}

void GameHolder::setDefenceAttack()
{
    allGame[0]->setDefence(allGame[OptionData::playerSize - 1]);
    for (int i = 1; i != OptionData::playerSize; ++i){
	allGame[i]->setDefence(allGame[i - 1]);
    }
    allGame[OptionData::playerSize - 1]->setAttack(allGame[0]);
    for (int i = 0; i != OptionData::playerSize - 1; ++i){
	allGame[i]->setAttack(allGame[i + 1]);
    }    
}

void GameHolder::setRandomQueue()
{
    for (int i = 0; i != StableData::playerSizeMax; ++i){
	delete allRandomQueueData[i];
	delete allRandomQueue[i];
    }
    
    for (int i = 0; i != StableData::playerSizeMax; ++i){
	allRandomQueueData[i] = NULL;
	allRandomQueue[i] = NULL;
    }
    
    for (int i = 0; i != OptionData::playerSize; ++i){
	RandomQueueData* &queue = allRandomQueueData[OptionData::allPlayerData[i]->randomQueueDataIndex];
	if (queue == NULL){
	    switch (OptionData::allPlayerData[i]->randomizerType){
	    case PlayerData::BAG:
		queue = new RandomQueueData(new BagRandomizer());
		break;
	    case PlayerData::HISTORY4ROLL:
		queue = new RandomQueueData(
			new HistoryRollRandomizer<4>(
			    StableData::history4Roll));
		break;
	    }
	}
	allRandomQueue[i] = new RandomQueue(queue);
	allGame[i]->setRandomQueue(allRandomQueue[i]);
    }    
}

void GameHolder::initGhostColor()
{
    double ghostAlpha = (double)OptionData::ghostAlpha / 100;
    
    for (int i = 0; i != sizeof(minoColor) / sizeof(*minoColor); ++i){
	minoGhostColor[i].r =
	    minoColor[i].r * ghostAlpha +
	    minoColor[BACKCOLOR].r * (1 - ghostAlpha);
	minoGhostColor[i].g =
	    minoColor[i].g * ghostAlpha +
	    minoColor[BACKCOLOR].g * (1 - ghostAlpha);
	minoGhostColor[i].b =
	    minoColor[i].b * ghostAlpha +
	    minoColor[BACKCOLOR].b * (1 - ghostAlpha);
    }
}


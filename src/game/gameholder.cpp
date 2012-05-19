#include "gameholder.h"
#include "valuesetter.h"

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
	allGame[i] = new Game(OptionData::allPlayerData[i], allGame);
    }
    
    setRandomQueue();
    setAllGameStatus(Game::PREPARE);
    
    OptionData::gameHolderStatus = OptionData::READY;
    ResourceData::sound->randomPlayMusic();
}

GameHolder::~GameHolder()
{
    SDL_FreeSurface(quitLabelBackSurface);
    delete quitLabel;
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
		SDL_Rect quitLabelRectTemp = quitLabelRect.getSDL_Rect();
		SDL_BlitSurface(ResourceData::display, &quitLabelRectTemp,
				quitLabelBackSurface, NULL);
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
		SDL_Rect quitLabelBackRectTemp = quitLabelRect.getSDL_Rect();
		SDL_BlitSurface(quitLabelBackSurface, NULL,
				ResourceData::display, &quitLabelBackRectTemp);
		OptionData::gameHolderStatus = OptionData::RUN;
	    } else if (sym == SDLK_RETURN){
		if (quitLabel->getToggle())
		    OptionData::gameHolderStatus = OptionData::QUITGAME;
		else{
		    SDL_Rect quitLabelBackRectTemp = quitLabelRect.getSDL_Rect();
		    SDL_BlitSurface(quitLabelBackSurface, NULL,
				    ResourceData::display, &quitLabelBackRectTemp);
		    OptionData::gameHolderStatus = OptionData::RUN;
		}
	    }
	    quitLabel->handleEvent(event);
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
	    setRandomQueue();
	    setAllGameStatus(Game::PREPARE);
	    OptionData::gameHolderStatus = OptionData::READY;
	}
	for (int i = 0; i != OptionData::playerSize; ++i){
	    allGame[i]->update();
	}	
	break;
    case OptionData::PAUSE:
	SDL_Rect quitLabelBackRectTemp = quitLabelRect.getSDL_Rect();
	SDL_BlitSurface(quitLabelBackSurface, NULL,
			ResourceData::display, &quitLabelBackRectTemp);
	quitLabel->update();
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

/**
   @see RandomQueueData
 */
void GameHolder::setRandomQueue()
{
    for (int i = 0; i != StableData::playerSizeMax; ++i){
	delete allRandomQueueData[i];
	delete allRandomQueue[i];
	allRandomQueueData[i] = NULL;
	allRandomQueue[i] = NULL;
    }
    
    for (int i = 0; i != OptionData::playerSize; ++i){
	RandomQueueData* &queue = allRandomQueueData[OptionData::allPlayerData[i]->randomQueueDataIndex - 1];
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

/**
   注意这个地方不仅存储了要打印在 display 上的 surface，还需要存储当前的被
   quitLabel 所覆盖的背景，不然由于玩家的方块的显示都是改变了才贴图的并且没有贴
   背景，会导致 quitLabel 残留在中间。
 */
void GameHolder::initQuitLabel()
{
    quitLabelRect = Rect<int>(0, 0, 200, 50);
    quitLabelBackSurface = SDL_CreateRGBSurface(
	ResourceData::display->flags,
	quitLabelRect.diagonal.x,
	quitLabelRect.diagonal.y,
	ResourceData::display->format->BitsPerPixel,
	ResourceData::display->format->Rmask,
	ResourceData::display->format->Gmask,
	ResourceData::display->format->Bmask,
	ResourceData::display->format->Amask);
    
    quitLabelRect.setCenter(StableData::screenSize / 2);
    quitLabel = new QuitLabel(quitLabelRect, "Quit?");
    quitLabel->setAction(new ValueSetter<OptionData::GameHolderStatus>(
			     OptionData::gameHolderStatus,
			     OptionData::QUITGAME));    
}

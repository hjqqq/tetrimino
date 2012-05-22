#include "color.h"
#include "gameholder.h"
#include "valuesetter.h"

GameHolder::GameHolder()
{
    initGhostColor();
    initPixPos();
    initMinoSurface();
    initQuitLabel();
    
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
    freeMinoSurface();
    delete quitLabel;
    SDL_FreeSurface(quitLabelBackSurface);
    
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
	if (event.type == SDL_KEYDOWN){
	    SDLKey sym = event.key.keysym.sym;
	    if (sym == SDLK_ESCAPE){
		SDL_Rect quitLabelRectTemp = quitLabelRect.getSDL_Rect();
		SDL_BlitSurface(ResourceData::display, &quitLabelRectTemp,
				quitLabelBackSurface, NULL);
		OptionData::gameHolderStatus = OptionData::PAUSE;
		pausePrevStatus = OptionData::READY;
	    }
	}	
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
		pausePrevStatus = OptionData::RUN;
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
		OptionData::gameHolderStatus = pausePrevStatus;
	    } else if (sym == SDLK_RETURN){
		if (quitLabel->getToggle())
		    OptionData::gameHolderStatus = OptionData::QUITGAME;
		else{
		    SDL_Rect quitLabelBackRectTemp = quitLabelRect.getSDL_Rect();
		    SDL_BlitSurface(quitLabelBackSurface, NULL,
				    ResourceData::display, &quitLabelBackRectTemp);
		    OptionData::gameHolderStatus = pausePrevStatus;
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
   这里使用了先设置空指针，再用 player 的编号（0， 1， 2， 3）找到对应
   RandomQueue 的办法。

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

/**
   初始化 minoGhostColor（全局变量 blockdata.h）, 采用与背景颜色直接计算RGB值的
   方法，ghostColor = color * alpha + back * (1 - alpha);
 */
void GameHolder::initGhostColor()
{
    double ghostAlpha = (double)OptionData::ghostAlpha / 100;
    
    for (int i = 0; i != sizeof(minoColor) / sizeof(*minoColor); ++i){
	minoGhostColor[i] = alpha_translate(minoColor[i], minoColor[BACKCOLOR], ghostAlpha);
    }
}

void GameHolder::initPixPos()
{
    int pixSizeX = StableData::screenSizeX / OptionData::playerSize;
    int minoPixSizeX = pixSizeX / 18;
    int minoPixSizeY = StableData::screenSizeY / 30;

    OptionData::minoPixSizeX = OptionData::minoPixSizeY =
	std::min(minoPixSizeX, minoPixSizeY);
    OptionData::minoPixSize = Vector2<int>(
	OptionData::minoPixSizeX,
	OptionData::minoPixSizeY);

    for (int i = 0; i != OptionData::playerSize; ++i){
	OptionData::allPlayerData[i]->showPixPos =
	    Vector2<int>(pixSizeX * i, 0);
    }
}

void GameHolder::initMinoSurface()
{
    SDL_Surface *minoTextureSurface = image_load("res/minotexture.png");
    SDL_Surface *backTextureSurface = image_load("res/backtexture.png");

    SDL_LockSurface(minoTextureSurface);
    SDL_LockSurface(backTextureSurface);
    for (int k = 0; k <= BACKCOLOR; ++k){
	minoSurface[k] = create_surface(
	    OptionData::minoPixSizeX, OptionData::minoPixSizeY);
	SDL_LockSurface(minoSurface[k]);
	
	minoGhostSurface[k] = create_surface(
	    OptionData::minoPixSizeX, OptionData::minoPixSizeY);
	SDL_LockSurface(minoGhostSurface[k]);
	
	halfMinoSurface[k] = create_surface(
	    OptionData::minoPixSizeX / 2, OptionData::minoPixSizeY / 2);
	SDL_LockSurface(halfMinoSurface[k]);		
    }
    
    Uint32 pixel;
    SDL_Color color;
    for (int k = 0; k != BACKCOLOR; ++k){
	for (int j = 0; j != OptionData::minoPixSizeY; ++j){
	    for (int i = 0; i != OptionData::minoPixSizeX; ++i){
		pixel = getPixel(
		    minoTextureSurface,
		    lerp(0, i, (double)minoTextureSurface->w /
			 OptionData::minoPixSizeX),
		    lerp(0, j, (double)minoTextureSurface->h /
			 OptionData::minoPixSizeY));
		color = Uint322SDL_Color(pixel);

		putPixel(minoSurface[k], i, j,
			 SDL_Color2Uint32(
			     multiply_translate(minoColor[k], color)));
		
		putPixel(minoGhostSurface[k], i, j,
			 SDL_Color2Uint32(
			     multiply_translate(minoGhostColor[k], color)));
	    }
	}
    }

    for (int j = 0; j != OptionData::minoPixSizeY; ++j){
	for (int i = 0; i != OptionData::minoPixSizeX; ++i){
	    pixel = getPixel(
		backTextureSurface,
		lerp(0, i, (double)backTextureSurface->w /
		     OptionData::minoPixSizeX),
		lerp(0, j, (double)backTextureSurface->h /
		     OptionData::minoPixSizeY));
	    color = Uint322SDL_Color(pixel);

	    putPixel(minoSurface[BACKCOLOR], i, j,
		     SDL_Color2Uint32(
			 screen_translate(minoColor[BACKCOLOR], color)));
		
	    putPixel(minoGhostSurface[BACKCOLOR], i, j,
		     SDL_Color2Uint32(
			 screen_translate(minoGhostColor[BACKCOLOR], color)));
	}
    }

    for (int k = 0; k <= BACKCOLOR; ++k){
	for (int j = 0; j != OptionData::minoPixSizeY / 2; ++j){
	    for (int i = 0; i != OptionData::minoPixSizeX / 2; ++i){
		pixel = getPixel(
		    minoSurface[k],
		    lerp(0, i, 2),
		    lerp(0, j, 2));
		
		putPixel(halfMinoSurface[k], i, j, pixel);
	    }
	}
    }

    for (int k = 0; k <= BACKCOLOR; ++k){
	SDL_UnlockSurface(minoSurface[k]);
	SDL_UnlockSurface(minoGhostSurface[k]);
	SDL_UnlockSurface(halfMinoSurface[k]);		
    }
    SDL_UnlockSurface(minoTextureSurface);    
    SDL_UnlockSurface(backTextureSurface);
    
    SDL_FreeSurface(minoTextureSurface);    
    SDL_FreeSurface(backTextureSurface);
}

void GameHolder::freeMinoSurface()
{
    for (int k = 0; k != 9; ++k){
	SDL_FreeSurface(minoSurface[k]);
	SDL_FreeSurface(minoGhostSurface[k]);
	SDL_FreeSurface(halfMinoSurface[k]);	
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
    quitLabelBackSurface = create_surface(
	quitLabelRect.diagonal.x, quitLabelRect.diagonal.y);
    quitLabelRect.setCenter(StableData::screenSize / 2);
    quitLabel = new QuitLabel(quitLabelRect, "Quit?", white);
}

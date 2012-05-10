#include "gameholder.h"

GameHolder::GameHolder()
{
    initGhostColor();

    SDL_BlitSurface(ResourceData::background, 0,
		    ResourceData::display, 0);
    
    for (int i = 0; i != StableData::playerSizeMax; ++i){
	allRandomQueueData[i] = NULL;	
	allGame[i] = NULL;		
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
	allGame[i] = new Game(OptionData::allPlayerData[i],
			      new RandomQueue(queue));
    }

    allGame[0]->setDefence(allGame[OptionData::playerSize - 1]);
    for (int i = 1; i != OptionData::playerSize; ++i){
	allGame[i]->setDefence(allGame[i - 1]);
    }
    allGame[OptionData::playerSize - 1]->setAttack(allGame[0]);
    for (int i = 0; i != OptionData::playerSize - 1; ++i){
	allGame[i]->setAttack(allGame[i + 1]);
    }
}

GameHolder::~GameHolder()
{
    for (int i = 0; i != StableData::playerSizeMax; ++i){
	delete allGame[i];
	delete allRandomQueueData[i];
    }
}

void GameHolder::handleEvent(const SDL_Event &event){
    for (int i = 0; i != OptionData::playerSize; ++i){
	allGame[i]->handleEvent(event);
    }
}
void GameHolder::update(){
    for (int i = 0; i != OptionData::playerSize; ++i){
	allGame[i]->update();
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


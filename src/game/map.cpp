#include <iostream>

#include "SDL.h"

#include "map.h"
#include "color.h"
#include "stabledata.h"
#include "optiondata.h"
#include "playerdata.h"
#include "utility.h"

void Map::update()
{
    updateBackGround();
    updateMap();
}

void Map::updateMap()
{
    Rect<int> blockRect = Rect<int>(0, 0,
				    StableData::blockPixSizeX,
				    StableData::blockPixSizeY);
    SDL_Rect tempRect;
    for (int i = 0; i != StableData::mapSizeX; ++i){
	for (int j = 0; j != StableData::mapSizeY; ++j){
	    if (playerData1.mapData[i][j] == 1){
		blockRect.setTopLeft(
		    playerData1.mapRect.getTopLeft() +
		    Vector2<int>(i * StableData::blockPixSizeX,
				 j * StableData::blockPixSizeY));
		tempRect = blockRect.getSDL_Rect();
		SDL_FillRect(OptionData::display,
			     &tempRect,
			     SDL_Color2Uint32(yellow));
	    }
	}
    }
}

void Map::updateBackGround()
{
    SDL_Rect mapRect = playerData1.mapRect.getSDL_Rect();
    SDL_FillRect(OptionData::display,
		 &mapRect,
		 SDL_Color2Uint32(black));
}

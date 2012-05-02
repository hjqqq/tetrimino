#include <iostream>

#include "SDL.h"

#include "mapshow.h"
#include "color.h"
#include "stabledata.h"
#include "optiondata.h"
#include "playerdata.h"
#include "utility.h"

using namespace StableData;

void MapShow::update()
{
    updateBackGround();
    updateMap();
}

void MapShow::updateMap()
{
    Rect<int> minoRect = Rect<int>(playerData1.mapPixRect.getTopLeft(),
				   minoPixSize);
    SDL_Rect drawRectTemp;

    for (int j = 0; j != mapSize.y; ++j){
	for (int i = 0; i != mapSize.x; ++i){
	    if (playerData1.mapData[i][j] == 1){
		Rect<int> drawRect(minoRect);
		drawRect.move(i * minoPixSize.x, j * minoPixSize.y);
		drawRectTemp = drawRect.getSDL_Rect();
		SDL_FillRect(OptionData::display,
			     &drawRectTemp,
			     SDL_Color2Uint32(yellow));
	    }
	}
    }
}

void MapShow::updateBackGround()
{
    SDL_Rect mapRectTemp = playerData1.mapPixRect.getSDL_Rect();
    SDL_FillRect(OptionData::display,
		 &mapRectTemp,
		 SDL_Color2Uint32(black));
}

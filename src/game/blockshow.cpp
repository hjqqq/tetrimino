#include <iostream>

#include "SDL_draw.h"

#include "color.h"
#include "utility.h"
#include "stabledata.h"
#include "optiondata.h"
#include "playerdata.h"
#include "blockshow.h"
#include "rect.h"

using namespace StableData;

void BlockShow::update()
{
    const BlockData &blockData = blockDataArray[playerData1.currentBlockShape];
    
    const BlockData::BlockNum &blockNum = blockData.getNum(
	playerData1.currentDirection);

    const Rect<int> &origBlockRect =
	blockData.getRect(playerData1.currentDirection);
    const Vector2<int> origBlockRectTopLeft = origBlockRect.getTopLeft();
    const Vector2<int> origBlockRectBottomRight = origBlockRect.getBottomRight();
    
    Rect<int> blockRect = origBlockRect;
    blockRect.move(playerData1.blockPos);

    Vector2<int> blockRectTopLeft = blockRect.getTopLeft();
    Vector2<int> blockRectBottomRight = blockRect.getBottomRight();
    
    Rect<int> minoRect(playerData1.mapPixRect.getTopLeft(),
		       minoPixSize);
    SDL_Rect drawRectTemp;

    for (int j = blockRectBottomRight.y - 1, origJ = origBlockRectBottomRight.y - 1;
	 j >= blockRectTopLeft.y && j >= 0;
	 --j, --origJ){
	    
    	for (int i = blockRectTopLeft.x, origI = origBlockRectTopLeft.x;
	     i != blockRectBottomRight.x;
	     ++i, ++origI){
	    
	    if (blockNum[origI][origJ] == 1){
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

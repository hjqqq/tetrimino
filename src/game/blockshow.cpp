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
    const int size = blockData.getSize();
    Rect<int> blockRect = blockData.getRect(
	playerData1.currentDirection);
    if (playerData1.blockPos.y < 0)
	blockRect.pos.y = std::max(blockRect.pos.y, -playerData1.blockPos.y);
    Vector2<int> blockRectTopLeft = blockRect.getTopLeft();
    Vector2<int> blockRectBottomRight = blockRect.getBottomRight();

    Vector2<int> blockPixTopLeft = playerData1.mapPixRect.getTopLeft();
    blockPixTopLeft.x += playerData1.blockPos.x * minoPixSize.x;
    blockPixTopLeft.y += playerData1.blockPos.y * minoPixSize.y;

    Rect<int> minoRect(blockPixTopLeft, minoPixSize);
    SDL_Rect drawRectTemp;
    for (int j = blockRectTopLeft.y; j != blockRectBottomRight.y; ++j){
	for (int i = blockRectTopLeft.x; i != blockRectBottomRight.x; ++i){
	    if (blockNum[i][j] == 1){

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

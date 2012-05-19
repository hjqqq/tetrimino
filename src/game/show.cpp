#include "SDL.h"
#include "SDL_draw.h"

#include "vector2.h"
#include "color.h"
#include "utility.h"
#include "blockdata.h"
#include "show.h"

Show::Show(PlayerData *_playerData):
    playerData(_playerData)
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
  
    halfMinoPixSize = OptionData::minoPixSize / 2;
    blockPixRect = Rect<int>(Vector2<int>(0, 0),
			     Vector2<int>(
				 OptionData::minoPixSize.x * 4,
				 OptionData::minoPixSize.y * 4));
    halfBlockPixRect = Rect<int>(
	Vector2<int>(0, 0),
	Vector2<int>(halfMinoPixSize.x * 4,
		     halfMinoPixSize.y * 4));
    
    nextPixPos = toPixPos(Vector2<int>(StableData::mapSize.x / 2 + 1, 1));
    nextPixRect = blockPixRect;
    nextPixRect.move(nextPixPos);
    nextPixRectTemp = nextPixRect.getSDL_Rect();
    
    smallNextPixPos = toPixPos(Vector2<int>(1, 6));
    
    mapPixPos = toPixPos(Vector2<int>(4, 6));
    mapPixRect = Rect<int>(
	mapPixPos,
	Vector2<int>(OptionData::minoPixSize.x * StableData::mapSize.x,
		     OptionData::minoPixSize.y * StableData::mapSize.y));
    
    holdPixPos = toPixPos(Vector2<int>(StableData::mapSize.x + 2, 3));
    holdPixRect = halfBlockPixRect;
    holdPixRect.move(holdPixPos);
    holdPixRectTemp = holdPixRect.getSDL_Rect();

    growBarPixPos = toPixPos(Vector2<int>(StableData::mapSize.x + 5, 6));
    growBarPixRect = Rect<int>(
	growBarPixPos,
	Vector2<int>(halfMinoPixSize.x,
		     OptionData::minoPixSize.y * StableData::mapSize.y));
    growBarPixRectTemp = growBarPixRect.getSDL_Rect();

    SDL_FillRect(ResourceData::display,
		 &growBarPixRectTemp,
		 SDL_Color2Uint32(minoColor[BACKCOLOR]));
}

void Show::blockShow(const Vector2<int> &pixPos,
		     const Vector2<int> &pos,
		     BlockShape shape,
		     Direction direction,
		     const Vector2<int> &minoPixSize,
		     const SDL_Color *minoColor)
{
    const BlockData &blockData = blockDataArray[shape];
    
    const BlockData::BlockNum &blockNum = blockData.getNum(direction);

    const Rect<int> &origBlockRect = blockData.getRect(direction);
    const Vector2<int> origBlockRectTopLeft = origBlockRect.getTopLeft();
    const Vector2<int> origBlockRectBottomRight = origBlockRect.getBottomRight();
    
    Rect<int> blockRect = origBlockRect;
    blockRect.move(pos);
    Vector2<int> blockRectTopLeft = blockRect.getTopLeft();
    Vector2<int> blockRectBottomRight = blockRect.getBottomRight();
    
    Rect<int> minoRect(pixPos, minoPixSize);
    Rect<int> drawRect;
    SDL_Rect drawRectTemp;

    for (int j = blockRectBottomRight.y - 1, origJ = origBlockRectBottomRight.y - 1;
	 j >= blockRectTopLeft.y && j >= 0;
	 --j, --origJ){
	    
    	for (int i = blockRectTopLeft.x, origI = origBlockRectTopLeft.x;
	     i != blockRectBottomRight.x;
	     ++i, ++origI){

	    if (blockNum[origI][origJ] != EMPTY){
		drawRect = minoRect;
		drawRect.move(i * minoPixSize.x, j * minoPixSize.y);
		drawRectTemp = drawRect.getSDL_Rect();
		SDL_FillRect(ResourceData::display,
			     &drawRectTemp,
			     SDL_Color2Uint32(minoColor[shape]));
	    }
	}
    }
}

void Show::previewShow(RandomQueue::iterator start,
			RandomQueue::iterator finish)
{
    nextShow(BlockShape(*start));
    smallNextShow(start + 1, finish);
}

void Show::nextShow(BlockShape shape)
{
    SDL_BlitSurface(ResourceData::background, &nextPixRectTemp,
		    ResourceData::display, &nextPixRectTemp);
    blockShow(nextPixPos,
	      Vector2<int>(0, 0),
	      shape,
	      NORTH,
	      OptionData::minoPixSize,
	      minoColor);
}

void Show::smallNextShow(RandomQueue::iterator start,
			 RandomQueue::iterator finish)
{
    Rect<int> smallNextPixRect = halfBlockPixRect;
    
    SDL_Rect smallNextPixRectTemp;
    
    Vector2<int> startPixPos = smallNextPixPos;
    for (RandomQueue::iterator iter = start; iter != finish; ++iter){
	smallNextPixRect.setTopLeft(startPixPos);
	smallNextPixRectTemp = smallNextPixRect.getSDL_Rect();
	SDL_BlitSurface(ResourceData::background, &smallNextPixRectTemp,
			ResourceData::display, &smallNextPixRectTemp);	
	
	blockShow(startPixPos,
		  Vector2<int>(0, 0),
		  BlockShape(*iter),
		  NORTH,
		  halfMinoPixSize,
		  minoColor);
	startPixPos.y += halfMinoPixSize.y * 6;
    }
}

void Show::dropBlockShow(Vector2<int> pos,
			 BlockShape shape,
			 Direction direction)
{
    blockShow(mapPixPos,
	      pos,
	      shape,
	      direction,
	      OptionData::minoPixSize,
	      minoColor);
}

void Show::mapShow(int mapData[StableData::mapSizeX][StableData::mapSizeY])
{
    Rect<int> minoRect = Rect<int>(mapPixPos,
				   OptionData::minoPixSize);
    Rect<int> drawRect;
    SDL_Rect drawRectTemp;

    for (int j = 0; j != StableData::mapSize.y; ++j){
	for (int i = 0; i != StableData::mapSize.x; ++i){
	    drawRect = minoRect;
	    drawRect.move(i * OptionData::minoPixSize.x,
			  j * OptionData::minoPixSize.y);
	    drawRectTemp = drawRect.getSDL_Rect();
	    SDL_FillRect(ResourceData::display,
			 &drawRectTemp,
			 SDL_Color2Uint32(minoColor[mapData[i][j]]));
	}
    }
}

void Show::holdShow(BlockShape holdShape)
{
    if (playerData->holder){
	SDL_BlitSurface(ResourceData::background, &holdPixRectTemp,
			ResourceData::display, &holdPixRectTemp);	    
	blockShow(holdPixPos,
		  Vector2<int>(0, 0),
		  holdShape,
		  NORTH,
		  halfMinoPixSize,
		  minoColor);
    }
}

void Show::ghostShow(Vector2<int> pos,
		     BlockShape shape,
		     Direction direction)
{
    if (playerData->ghost){
	blockShow(mapPixPos,
		  pos,
		  shape,
		  direction,
		  OptionData::minoPixSize,
		  minoGhostColor);
    }
}

void Show::growBarShow(int mapGrow)
{ 
    SDL_FillRect(ResourceData::display,
		 &growBarPixRectTemp,
		 SDL_Color2Uint32(minoColor[BACKCOLOR]));

    Rect<int> growFillPixRect(
	0, 0,
	halfMinoPixSize.x, mapGrow * OptionData::minoPixSize.y);
    
    growFillPixRect.setBottomLeft(growBarPixRect.getBottomLeft());

    SDL_Rect growFillPixRectTemp(growFillPixRect.getSDL_Rect());
    SDL_FillRect(ResourceData::display,
		 &growFillPixRectTemp,
		 SDL_Color2Uint32(minoColor[GARBAGECOLOR]));    
}

void Show::messageShow(std::string str)
{
    SDL_Surface *messageSurface = TTF_RenderText_Solid(
	ResourceData::font, str.c_str(), white);
    Rect<int> blitRect(get_rect(messageSurface));
    blitRect.setCenter(mapPixRect.getCenter());
    SDL_Rect blitRectTemp = blitRect.getSDL_Rect();
    SDL_BlitSurface(messageSurface, NULL,
		    ResourceData::display, &blitRectTemp);
    SDL_FreeSurface(messageSurface);
}


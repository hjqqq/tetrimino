#ifndef SHOW_H
#define SHOW_H

#include <string>

#include "SDL.h"

#include "randomqueue.h"
#include "blockdata.h"

class Show{
public:
    Show(PlayerData *_playerData);
    void blockShow(const Vector2<int> &pixPos,
		   const Vector2<int> &pos,
		   BlockShape shape,
		   Direction direction,
		   const Vector2<int> &minoPixSize,
		   SDL_Surface **minoSurface);
    
    void previewShow(RandomQueue::iterator start,
		     RandomQueue::iterator finish);
    
    void nextShow(BlockShape shape);
    void smallNextShow(RandomQueue::iterator start,
		       RandomQueue::iterator finish);

    void dropBlockShow(Vector2<int> pos,
		       BlockShape shape,
		       Direction direction);
    
    void mapShow(int mapData[StableData::mapSizeX][StableData::mapSizeY]);
    void holdShow(BlockShape holdShape);

    void ghostShow(Vector2<int> pos,
		   BlockShape shape,
		   Direction direction);
    void growBarShow(int mapGrow);
    
    void messageShow(std::string str);
    
private:
    inline Vector2<int> toPixPos(const Vector2<int> orig);
    PlayerData *playerData;
    Vector2<int> halfMinoPixSize;
    Rect<int> blockPixRect;
    Rect<int> halfBlockPixRect;
    
    Vector2<int> nextPixPos;
    Rect<int> nextPixRect;
    SDL_Rect nextPixRectTemp;
    
    Vector2<int> smallNextPixPos;
    
    Vector2<int> mapPixPos;
    Rect<int> mapPixRect;
    
    Vector2<int> holdPixPos;
    Rect<int> holdPixRect;
    SDL_Rect holdPixRectTemp;
    
    Vector2<int> growBarPixPos;
    Rect<int> growBarPixRect;
    SDL_Rect growBarPixRectTemp;
};

inline Vector2<int> Show::toPixPos(const Vector2<int> orig)
{
    return Vector2<int>(orig.x * OptionData::minoPixSize.x,
			orig.y * OptionData::minoPixSize.y) +
	playerData->showPixPos;
}

#endif

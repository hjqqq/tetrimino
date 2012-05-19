#ifndef BLOCKDATA_H
#define BLOCKDATA_H

#include <vector>

#include "color.h"
#include "rect.h"

/**
   @file blockdata.h
 */

enum Direction{NORTH, WEST, SOUTH, EAST};
enum BlockShape{ISHAPE, JSHAPE, LSHAPE, SSHAPE, TSHAPE, ZSHAPE, OSHAPE};

/**
   @brief 存着所有与下落方块有关的数据。

   包括方块的形状（int[4][4][4] 4个方向 加 4 * 4），方块的Rect（表示有方块存在
   的区域）。定义全局数组（blockDataArray, blockStartPosArray），以方块形状为下
   标可以取得方块的形状，Rect信息，以及初始位置信息。MinoColor定义了每一个方块
   中的小方格的颜色。这个颜色就直接作为int存到了方块数据里面。
 */
class BlockData{
public:
    typedef int BlockNum[4][4];
    typedef BlockNum AllBlockNum[4];

    typedef Rect<int> BlockRect;
    typedef BlockRect AllBlockRect[4];

    inline BlockData(int _size,
	      const AllBlockNum &_allBlockNum,
	      const AllBlockRect &_allBlockRect);
    
    inline int getSize() const;
    
    inline const BlockNum& getNum(
	Direction direction) const;
    
    inline const BlockRect& getRect(
	Direction direction) const;
    
private:
    int size;
    const AllBlockNum &allBlockNum;
    const AllBlockRect &allBlockRect;
};

const int blockPackageSize = 7;
extern const BlockData blockDataI;
extern const BlockData blockDataJ;
extern const BlockData blockDataL;
extern const BlockData blockDataS;
extern const BlockData blockDataT;
extern const BlockData blockDataZ;
extern const BlockData blockDataO;
extern const BlockData blockDataArray[blockPackageSize];

extern const Vector2<int> blockStartPosI;
extern const Vector2<int> blockStartPosJLSTZ;
extern const Vector2<int> blockStartPosO;
extern const Vector2<int> blockStartPosArray[blockPackageSize];

enum MinoColor{ICOLOR, JCOLOR, LCOLOR,
	       SCOLOR, TCOLOR, ZCOLOR,
	       OCOLOR, GARBAGECOLOR, BACKCOLOR, EMPTY};
extern const SDL_Color minoColor[9];
extern SDL_Color minoGhostColor[9];

BlockData::BlockData(int _size,
		     const AllBlockNum &_allBlockNum,
		     const AllBlockRect &_allBlockRect):
    size(_size),
    allBlockNum(_allBlockNum),
    allBlockRect(_allBlockRect)
{}

int BlockData::getSize() const
{
    return size;
}

const BlockData::BlockNum& BlockData::getNum(
    Direction direction) const
{
    return allBlockNum[direction];
}

const BlockData::BlockRect& BlockData::getRect(
    Direction direction) const
{
    return allBlockRect[direction];
}

#endif

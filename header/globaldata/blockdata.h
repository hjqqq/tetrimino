#ifndef BLOCKDATA_H
#define BLOCKDATA_H

#include <vector>

#include "rect.h"

class BlockData{
public:
    typedef int BlockNum[4][4];
    typedef BlockNum AllBlockNum[4];

    typedef Rect<int> BlockRect;
    typedef BlockRect AllBlockRect[4];

    enum Direction{NORTH, WEST, SOUTH, EAST};
    enum BlockShape{ISHAPE, LSHAPE, JSHAPE, SSHAPE, TSHAPE, ZSHAPE, OSHAPE};
    
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
extern const BlockData blockDataL;
extern const BlockData blockDataJ;
extern const BlockData blockDataS;
extern const BlockData blockDataT;
extern const BlockData blockDataZ;
extern const BlockData blockDataO;
extern const BlockData blockDataArray[blockPackageSize];

extern const Vector2<int> blockStartPosI;
extern const Vector2<int> blockStartPosLJSTZ;
extern const Vector2<int> blockStartPosO;
extern const Vector2<int> blockStartPosArray[blockPackageSize];

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

#ifndef BLOCKDATA_H
#define BLOCKDATA_H

#include <vector>

#include "stabledata.h"
#include "rect.h"

class BlockData{
public:
    typedef int BlockNum[4][4];
    typedef BlockNum AllBlockNum[4];

    typedef Rect BlockRect;
    typedef BlockRect AllBlockRect[4];
    
    inline BlockData(int _size,
	      const AllBlockNum &_allBlockNum,
	      const AllBlockRect &_allBlockRect);
    
    inline int getSize() const;
    
    inline const BlockNum& getNum(
	StableData::Direction direction) const;
    
    inline const BlockRect& getRect(
	StableData::Direction direction) const;
    
private:
    int size;
    const AllBlockNum &allBlockNum;
    const AllBlockRect &allBlockRect;
};

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
    StableData::Direction direction) const
{
    return allBlockNum[direction];
}

const BlockData::BlockRect& BlockData::getRect(
    StableData::Direction direction) const
{
    return allBlockRect[direction];
}

extern BlockData blockDataI;
extern BlockData blockDataL;
extern BlockData blockDataJ;
extern BlockData blockDataS;
extern BlockData blockDataT;
extern BlockData blockDataZ;
extern BlockData blockDataO;

extern BlockData blockDataArray[7];

#endif

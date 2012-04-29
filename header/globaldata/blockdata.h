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
    
    inline BlockData(int _blockSize,
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

BlockData::BlockData(int _blockSize,
		     const AllBlockData &_allBlockNum,
		     const AllBlockRect &_allBlockRect):
    blockSize(_blockSize),
    allBlockNum(_allBlockNum),
    allBlockRect(_allBlockRect)
{}

int BlockData::getSize() const
{
    return size;
}

const BlockData::BlockNum& getNum(
    StableData::Direction direction) const
{
    return allBlockNum[direction];
}

const BlockData::BlockRect& getRect(
    StableData::Direction direction) const
{
    return allBlockRect[direction];
}

extern const BlockData &blockDataI;
extern const BlockData &blockDataL;
extern const BlockData &blockDataJ;
extern const BlockData &blockDataS;
extern const BlockData &blockDataT;
extern const BlockData &blockDataZ;
extern const BlockData &blockDataO;

extern const BlockData &blockDataArray[7];

#endif

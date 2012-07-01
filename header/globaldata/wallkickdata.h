#ifndef WALLKICKDATA_H
#define WALLKICKDATA_H

#include "vector2.h"
#include "blockdata.h"

class WallKickData{
public:
    typedef Vector2<int> WallKickNum[5];
    typedef WallKickNum *AllWallKickNum[4][4];

    inline WallKickData(const AllWallKickNum &_allWallKickNum);
    inline const WallKickNum& getNum(
	Direction startDirection,
	Direction finishDirection) const;
private:
    const AllWallKickNum &allWallKickNum;
};

WallKickData::WallKickData(const AllWallKickNum &_allWallKickNum):
    allWallKickNum(_allWallKickNum)
{}

const WallKickData::WallKickNum& WallKickData::getNum(
    Direction startDirection,
    Direction finishDirection) const
{
    return *allWallKickNum[startDirection][finishDirection];
}
    
extern const WallKickData wallKickDataI;
extern const WallKickData wallKickDataL;
extern const WallKickData wallKickDataJ;
extern const WallKickData wallKickDataS;
extern const WallKickData wallKickDataT;
extern const WallKickData wallKickDataZ;
extern const WallKickData wallKickDataO;
extern const WallKickData wallKickDataArray[blockPackageSize];

#endif

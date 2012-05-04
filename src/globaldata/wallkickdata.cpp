#include "wallkickdata.h"

WallKickData::WallKickNum NONE = {
    Vector2<int>(0, 0),
    Vector2<int>(0, 0),    
    Vector2<int>(0, 0),
    Vector2<int>(0, 0),
    Vector2<int>(0, 0)        
};

WallKickData::WallKickNum IN2W = {
    Vector2<int>(0, 0),
    Vector2<int>(-1, 0),
    Vector2<int>(2, 0),
    Vector2<int>(-1, -2),
    Vector2<int>(2, 1)
};

WallKickData::WallKickNum IW2N = {
    Vector2<int>(0, 0),
    Vector2<int>(1, 0),
    Vector2<int>(-2, 0),
    Vector2<int>(1, 2),
    Vector2<int>(-2, -1)
};

WallKickData::WallKickNum IW2S = {
    Vector2<int>(0, 0),
    Vector2<int>(-2, 0),
    Vector2<int>(1, 0),
    Vector2<int>(2, -1),
    Vector2<int>(-2, -1)
};

WallKickData::WallKickNum IS2W = {
    Vector2<int>(0, 0),
    Vector2<int>(2, 0),
    Vector2<int>(-1, 0),
    Vector2<int>(2, -1),
    Vector2<int>(-1, 2)
};

WallKickData::WallKickNum IS2E = {
    Vector2<int>(0, 0),
    Vector2<int>(1, 0),
    Vector2<int>(-2, 0),
    Vector2<int>(1, 2),
    Vector2<int>(-2, -1)
};

WallKickData::WallKickNum IE2S = {
    Vector2<int>(0, 0),
    Vector2<int>(-1, 0),
    Vector2<int>(2, 0),
    Vector2<int>(-1, -2),
    Vector2<int>(2, 1)
};

WallKickData::WallKickNum IE2N = {
    Vector2<int>(0, 0),
    Vector2<int>(2, 0),
    Vector2<int>(-1, 0),
    Vector2<int>(2, -1),
    Vector2<int>(-1, 2)
};

WallKickData::WallKickNum IN2E = {
    Vector2<int>(0, 0),
    Vector2<int>(-2, 0),
    Vector2<int>(1, 0),
    Vector2<int>(-2, 1),
    Vector2<int>(1, -2)
};

WallKickData::AllWallKickNum INum{
    {NONE, IN2W, NONE, IN2E},
    {IW2N, NONE, IW2S, NONE},
    {NONE, IS2W, NONE, IS2E},
    {IE2N, NONE, IE2S, NONE}
};

const WallKickData wallKickDataI(INum);


WallKickData::WallKickNum LJSTZN2W = {
    Vector2<int>(0, 0),
    Vector2<int>(1, 0),
    Vector2<int>(1, -1),
    Vector2<int>(0, 2),
    Vector2<int>(1, 2)
};

WallKickData::WallKickNum LJSTZW2N = {
    Vector2<int>(0, 0),
    Vector2<int>(-1, 0),
    Vector2<int>(-1, 1),
    Vector2<int>(0, -2),
    Vector2<int>(-1, -2)
};

WallKickData::WallKickNum LJSTZW2S = {
    Vector2<int>(0, 0),
    Vector2<int>(-1, 0),
    Vector2<int>(-1, 1),
    Vector2<int>(0, -2),
    Vector2<int>(-1, -2)
};

WallKickData::WallKickNum LJSTZS2W = {
    Vector2<int>(0, 0),
    Vector2<int>(1, 0),
    Vector2<int>(1, -1),
    Vector2<int>(0, 2),
    Vector2<int>(1, 2)
};

WallKickData::WallKickNum LJSTZS2E = {
    Vector2<int>(0, 0),
    Vector2<int>(-1, 0),
    Vector2<int>(-1, -1),
    Vector2<int>(0, 2),
    Vector2<int>(-1, 2)
};

WallKickData::WallKickNum LJSTZE2S = {
    Vector2<int>(0, 0),
    Vector2<int>(1, 0),
    Vector2<int>(1, 1),
    Vector2<int>(0, -2),
    Vector2<int>(1, -2)
};

WallKickData::WallKickNum LJSTZE2N = {
    Vector2<int>(0, 0),
    Vector2<int>(1, 0),
    Vector2<int>(1, 1),
    Vector2<int>(0, -2),
    Vector2<int>(1, -2)
};

WallKickData::WallKickNum LJSTZN2E = {
    Vector2<int>(0, 0),
    Vector2<int>(-1, 0),
    Vector2<int>(-1, -1),
    Vector2<int>(0, 2),
    Vector2<int>(-1, 2)
};

WallKickData::AllWallKickNum LJSTZNum{
    {NONE    , LJSTZN2W, NONE    , LJSTZN2E},
    {LJSTZW2N, NONE    , LJSTZW2S, NONE    },
    {NONE    , LJSTZS2W, NONE    , LJSTZS2E},
    {LJSTZE2N, NONE    , LJSTZE2S, NONE    }
};

const WallKickData wallKickDataL(LJSTZNum);
const WallKickData wallKickDataJ(LJSTZNum);
const WallKickData wallKickDataS(LJSTZNum);
const WallKickData wallKickDataT(LJSTZNum);
const WallKickData wallKickDataZ(LJSTZNum);

WallKickData::AllWallKickNum ONum{
    {NONE, NONE, NONE, NONE},
    {NONE, NONE, NONE, NONE},
    {NONE, NONE, NONE, NONE},
    {NONE, NONE, NONE, NONE}
};

const WallKickData wallKickDataO(ONum);

const WallKickData wallKickDataArray[blockPackageSize] = {
    wallKickDataI,
    wallKickDataL,
    wallKickDataJ,
    wallKickDataS,
    wallKickDataT,
    wallKickDataZ,
    wallKickDataO
};

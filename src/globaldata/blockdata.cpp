#include "blockdata.h"

//----------------------------------------------------------------
BlockData::AllBlockNum I = {
    {{0, 0, 1, 0},
     {0, 0, 1, 0},
     {0, 0, 1, 0},
     {0, 0, 1, 0}},
    
    {{0, 0, 0, 0},
     {0, 0, 0, 0},
     {1, 1, 1, 1},
     {0, 0, 0, 0}},
    
    {{0, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 1, 0, 0}},
    
    {{0, 0, 0, 0},
     {1, 1, 1, 1},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}
};

BlockData::AllBlockRect IRect = {
    Rect<int>(0, 2, 4, 1),
    Rect<int>(2, 0, 1, 4),
    Rect<int>(0, 1, 4, 1),
    Rect<int>(1, 0, 1, 4)
};

const BlockData blockDataI(4, I, IRect);
const Vector2<int> blockStartPosI(3, -2);

//----------------------------------------------------------------
BlockData::AllBlockNum L = {
    {{1, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 0, 0, 0}},
    
    {{0, 0, 1, 0},
     {1, 1, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},
    
    {{0, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 1, 1, 0},
     {0, 0, 0, 0}},
    
    {{0, 0, 0, 0},
     {1, 1, 1, 0},
     {1, 0, 0, 0},
     {0, 0, 0, 0}}
};

BlockData::AllBlockNum J = {
    {{0, 1, 0, 0},
     {0, 1, 0, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0}},
    
    {{1, 0, 0, 0},
     {1, 1, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},
    
    {{0, 1, 1, 0},
     {0, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 0, 0, 0}},
    
    {{0, 0, 0, 0},
     {1, 1, 1, 0},
     {0, 0, 1, 0},
     {0, 0, 0, 0}},    
};

BlockData::AllBlockNum S = {
    {{0, 1, 0, 0},
     {1, 1, 0, 0},
     {1, 0, 0, 0},
     {0, 0, 0, 0}},
    
    {{1, 1, 0, 0},
     {0, 1, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},
    
    {{0, 0, 1, 0},
     {0, 1, 1, 0},
     {0, 1, 0, 0},
     {0, 0, 0, 0}},
    
    {{0, 0, 0, 0},
     {1, 1, 0, 0},
     {0, 1, 1, 0},
     {0, 0, 0, 0}}
};

BlockData::AllBlockNum T = {
    {{0, 1, 0, 0},
     {1, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 0, 0, 0}},
    
    {{0, 1, 0, 0},
     {1, 1, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},
    
    {{0, 1, 0, 0},
     {0, 1, 1, 0},
     {0, 1, 0, 0},
     {0, 0, 0, 0}},
    
    {{0, 0, 0, 0},
     {1, 1, 1, 0},
     {0, 1, 0, 0},
     {0, 0, 0, 0}}
};

BlockData::AllBlockNum Z = {
    {{1, 0, 0, 0},
     {1, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 0, 0, 0}},
    
    {{0, 1, 1, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},
    
    {{0, 1, 0, 0},
     {0, 1, 1, 0},
     {0, 0, 1, 0},
     {0, 0, 0, 0}},
    
    {{0, 0, 0, 0},
     {0, 1, 1, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0}}
};

BlockData::AllBlockRect LJSTZRect = {
    Rect<int>(0, 0, 3, 2),
    Rect<int>(0, 0, 2, 3),
    Rect<int>(0, 1, 3, 2),
    Rect<int>(1, 0, 2, 3)
};

const BlockData blockDataL(3, L, LJSTZRect);
const BlockData blockDataJ(3, J, LJSTZRect);
const BlockData blockDataS(3, S, LJSTZRect);
const BlockData blockDataT(3, T, LJSTZRect);
const BlockData blockDataZ(3, Z, LJSTZRect);

const Vector2<int> blockStartPosLJSTZ(3, -1);

//----------------------------------------------------------------

BlockData::AllBlockNum O = {
    {{1, 1, 0, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},
    
    {{1, 1, 0, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},
    
    {{1, 1, 0, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},
    
    {{1, 1, 0, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}
};

BlockData::AllBlockRect ORect = {
    Rect<int>(0, 0, 2, 2),
    Rect<int>(0, 0, 2, 2),
    Rect<int>(0, 0, 2, 2),
    Rect<int>(0, 0, 2, 2)
};

const BlockData blockDataO(2, O, ORect);
const Vector2<int> blockStartPosO(4, -1);

const BlockData blockDataArray[blockPackageSize] = {
    blockDataI,
    blockDataL,
    blockDataJ,
    blockDataS,
    blockDataT,
    blockDataZ,
    blockDataO
};

const Vector2<int> blockStartPosArray[blockPackageSize] = {
    blockStartPosI,
    blockStartPosLJSTZ,
    blockStartPosLJSTZ,
    blockStartPosLJSTZ,
    blockStartPosLJSTZ,
    blockStartPosLJSTZ,
    blockStartPosO
};

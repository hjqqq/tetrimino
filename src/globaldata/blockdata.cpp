#include "blockdata.h"
#include "stabledata.h"

//----------------------------------------------------------------
BlockData::AllBlockNum I = {
    {{9, 0, 9, 9},
     {9, 0, 9, 9},
     {9, 0, 9, 9},
     {9, 0, 9, 9}},
    
    {{9, 9, 9, 9},
     {0, 0, 0, 0},
     {9, 9, 9, 9},
     {9, 9, 9, 9}},
    
    {{9, 9, 0, 9},
     {9, 9, 0, 9},
     {9, 9, 0, 9},
     {9, 9, 0, 9}},
    
    {{9, 9, 9, 9},
     {9, 9, 9, 9},
     {0, 0, 0, 0},
     {9, 9, 9, 9}}
};

BlockData::AllBlockRect IRect = {
    Rect<int>(0, 1, 4, 1),
    Rect<int>(1, 0, 1, 4),
    Rect<int>(0, 2, 4, 1),
    Rect<int>(2, 0, 1, 4)
};

const BlockData blockDataI(4, I, IRect);
const Vector2<int> blockStartPosI(StableData::mapSize.x / 2 - 2, -1);

//----------------------------------------------------------------
BlockData::AllBlockNum J = {
    {{9, 9, 9, 9},
     {9, 1, 1, 9},
     {9, 9, 1, 9},
     {9, 9, 1, 9}},
    
    {{9, 9, 9, 9},
     {9, 9, 9, 1},
     {9, 1, 1, 1},
     {9, 9, 9, 9}},
    
    {{9, 9, 9, 9},
     {9, 9, 1, 9},
     {9, 9, 1, 9},
     {9, 9, 1, 1}},
    
    {{9, 9, 9, 9},
     {9, 9, 9, 9},
     {9, 1, 1, 1},
     {9, 1, 9, 9}}
};

BlockData::AllBlockNum L = {
    {{9, 9, 9, 9},
     {9, 9, 2, 9},
     {9, 9, 2, 9},
     {9, 2, 2, 9}},
    
    {{9, 9, 9, 9},
     {9, 2, 9, 9},
     {9, 2, 2, 2},
     {9, 9, 9, 9}},
    
    {{9, 9, 9, 9},
     {9, 9, 2, 2},
     {9, 9, 2, 9},
     {9, 9, 2, 9}},
    
    {{9, 9, 9, 9},
     {9, 9, 9, 9},
     {9, 2, 2, 2},
     {9, 9, 9, 2}},    
};

BlockData::AllBlockNum S = {
    {{9, 9, 9, 9},
     {9, 9, 3, 9},
     {9, 3, 3, 9},
     {9, 3, 9, 9}},
    
    {{9, 9, 9, 9},
     {9, 3, 3, 9},
     {9, 9, 3, 3},
     {9, 9, 9, 9}},
    
    {{9, 9, 9, 9},
     {9, 9, 9, 3},
     {9, 9, 3, 3},
     {9, 9, 3, 9}},
    
    {{9, 9, 9, 9},
     {9, 9, 9, 9},
     {9, 3, 3, 9},
     {9, 9, 3, 3}}
};

BlockData::AllBlockNum T = {
    {{9, 9, 9, 9},
     {9, 9, 4, 9},
     {9, 4, 4, 9},
     {9, 9, 4, 9}},
    
    {{9, 9, 9, 9},
     {9, 9, 4, 9},
     {9, 4, 4, 4},
     {9, 9, 9, 9}},
    
    {{9, 9, 9, 9},
     {9, 9, 4, 9},
     {9, 9, 4, 4},
     {9, 9, 4, 9}},
    
    {{9, 9, 9, 9},
     {9, 9, 9, 9},
     {9, 4, 4, 4},
     {9, 9, 4, 9}}
};

BlockData::AllBlockNum Z = {
    {{9, 9, 9, 9},
     {9, 5, 9, 9},
     {9, 5, 5, 9},
     {9, 9, 5, 9}},
    
    {{9, 9, 9, 9},
     {9, 9, 5, 5},
     {9, 5, 5, 9},
     {9, 9, 9, 9}},
    
    {{9, 9, 9, 9},
     {9, 9, 5, 9},
     {9, 9, 5, 5},
     {9, 9, 9, 5}},
    
    {{9, 9, 9, 9},
     {9, 9, 9, 9},
     {9, 9, 5, 5},
     {9, 5, 5, 9}}
};

BlockData::AllBlockRect JLSTZRect = {
    Rect<int>(1, 1, 3, 2),
    Rect<int>(1, 1, 2, 3),
    Rect<int>(1, 2, 3, 2),
    Rect<int>(2, 1, 2, 3)
};

const BlockData blockDataJ(3, J, JLSTZRect);
const BlockData blockDataL(3, L, JLSTZRect);
const BlockData blockDataS(3, S, JLSTZRect);
const BlockData blockDataT(3, T, JLSTZRect);
const BlockData blockDataZ(3, Z, JLSTZRect);

const Vector2<int> blockStartPosJLSTZ(StableData::mapSize.x / 2 - 3, -2);

//----------------------------------------------------------------

BlockData::AllBlockNum O = {
    {{9, 9, 9, 9},
     {9, 6, 6, 9},
     {9, 6, 6, 9},
     {9, 9, 9, 9}},
    
    {{9, 9, 9, 9},
     {9, 6, 6, 9},
     {9, 6, 6, 9},
     {9, 9, 9, 9}},
    
    {{9, 9, 9, 9},
     {9, 6, 6, 9},
     {9, 6, 6, 9},
     {9, 9, 9, 9}},
    
    {{9, 9, 9, 9},
     {9, 6, 6, 9},
     {9, 6, 6, 9},
     {9, 9, 9, 9}}
};

BlockData::AllBlockRect ORect = {
    Rect<int>(1, 1, 2, 2),
    Rect<int>(1, 1, 2, 2),
    Rect<int>(1, 1, 2, 2),
    Rect<int>(1, 1, 2, 2)
};

const BlockData blockDataO(2, O, ORect);
const Vector2<int> blockStartPosO(StableData::mapSize.x / 2 - 2, -2);

const BlockData blockDataArray[blockPackageSize] = {
    blockDataI,
    blockDataJ,
    blockDataL,
    blockDataS,
    blockDataT,
    blockDataZ,
    blockDataO
};

const Vector2<int> blockStartPosArray[blockPackageSize] = {
    blockStartPosI,
    blockStartPosJLSTZ,
    blockStartPosJLSTZ,
    blockStartPosJLSTZ,
    blockStartPosJLSTZ,
    blockStartPosJLSTZ,
    blockStartPosO
};

const SDL_Color minoColor[9] = {
    cyan,
    blue,
    orange,
    green,
    purple,
    red,
    yellow,
    gray,
    black
};

SDL_Color minoGhostColor[9] = {
    cyan,
    blue,
    orange,
    green,
    purple,
    red,
    yellow,
    gray,
    black
};

SDL_Surface* minoSurface[9];
SDL_Surface* minoGhostSurface[9];
SDL_Surface* halfMinoSurface[9];

#ifndef STABLEDATA_H
#define STABLEDATA_H

#include <string>
#include <vector2.h>
#include "rect.h"

/**
   @file stabledata.h
 */

/**
   游戏中无法改变的常量
 */
struct StableData{
    static const std::string fontFile;
    static const std::string backgroundFile;
    static const Vector2 screenSize;
    static const Rect menuRect;
    
    static const int mapSizeX = 10;
    static const int mapSizeY = 20;
    static const Vector2 mapSize;
    static const int blockPackageSize;
    enum Direction{NORTH, WEST, SOUTH, EAST};
    enum BlockShape{ISHAPE, LSHAPE, SSHAPE, TSHAPE, ZSHAPE, OSHAPE};
};

#endif

#ifndef STABLEDATA_H
#define STABLEDATA_H

#include <string>

#include "vector2.h"
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
    static const int screenSizeX = 800;
    static const int screenSizeY = 600;
    static const Vector2<int> screenSize;

    static const Rect<int> menuRect;
    
    static const int mapSizeX = 10;
    static const int mapSizeY = 20;
    static const Vector2<int> mapSize;

    static const int blockPixSizeX = 20;
    static const int blockPixSizeY = 20;
    static const Vector2<int> blockPixSize;
    
    static const int blockPackageSize = 7;
    
    enum Direction{NORTH, WEST, SOUTH, EAST};
    enum BlockShape{ISHAPE, LSHAPE, SSHAPE, TSHAPE, ZSHAPE, OSHAPE};
};

#endif

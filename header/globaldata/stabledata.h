#ifndef STABLEDATA_H
#define STABLEDATA_H

#include <string>

#include "vector2.h"
#include "rect.h"
#include "blockdata.h"

/**
   @file stabledata.h
 */

/**
   游戏中无法改变的常量
 */
namespace StableData{
  //    const std::string fontFile("res/MINYN___.ttf");
    const std::string fontFile("res/comic.ttf");
    const std::string backgroundFile("res/back.jpg");
    const int fps = 60;
    
    const int screenSizeX = 800;
    const int screenSizeY = 600;
    const Vector2<int> screenSize(screenSizeX, screenSizeY);

    const Rect<int> menuRect(200, 100, 400, 400);
    const Rect<int> labelRect(0, 0, 400, 50);

    const int mapSizeX = 10;
    const int mapSizeY = 20;
    const Vector2<int> mapSize(mapSizeX, mapSizeY);

    const int playerSizeMax = 4;

    const int history4Roll[4] = {5, 3, 5, 3};
};

#endif

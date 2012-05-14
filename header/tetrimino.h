#ifndef TETRIMINO_H
#define TETRIMINO_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "utility.h"
#include "setting.h"

/**
   @file tetrimino.h
 */

/**
   @brief 俄罗斯方块游戏的入口。把一切联系起来。
 */

class Tetrimino{
public:
    Tetrimino();
    ~Tetrimino();
private:
    Setting menu_setting;

    void mainloop();
    void menuloop();
    void gameloop();
    void loadResource();
    void releaseResource();

};

#endif

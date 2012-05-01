#ifndef OPTIONDATA_H
#define OPTIONDATA_H

#include <string>
#include "SDL.h"
#include "SDL_ttf.h"

/**
   @file optiondata.h
 */

/**
   游戏中可以通过菜单选项改变的，游戏运行时才被赋值的变量。
 */

namespace OptionData{
    static SDL_Surface *display = NULL;
    static SDL_Surface *background = NULL;
    static TTF_Font *font = NULL;
    
    enum TetriminoStatus{MENULOOP, GAMELOOP, QUIT};
    static TetriminoStatus tetriminoStatus = GAMELOOP;
    
    enum MenuHolderStatus{MAINMENU, STARTMENU, OPTIONMENU, QUITMENU};
    static MenuHolderStatus menuHolderStatus = MAINMENU;

    enum GameHolderStatus{STARTGAME, QUITGAME};
    static GameHolderStatus gameHolderStatus = STARTGAME;
};

#endif

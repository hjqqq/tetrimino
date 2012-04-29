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

struct OptionData{
    static SDL_Surface *display;
    static SDL_Surface *background;
    static TTF_Font *font;
    
    enum TetriminoStatus{MENULOOP, GAMELOOP, QUIT};
    static TetriminoStatus tetriminoStatus;
    
    enum MenuHolderStatus{MAINMENU, STARTMENU, OPTIONMENU, QUITMENU};
    static MenuHolderStatus menuHolderStatus;

    enum GameHolderStatus{STARTGAME, QUITGAME};
    static GameHolderStatus gameHolderStatus;
};

#endif

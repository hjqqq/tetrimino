#ifndef OPTIONDATA_H
#define OPTIONDATA_H

#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "clock.h"

/**
   @file optiondata.h
 */

/**
   游戏中可以通过菜单选项改变的，游戏运行时才被赋值的变量。
 */

namespace OptionData{
    extern SDL_Surface *display;
    extern SDL_Surface *background;
    extern TTF_Font *font;
    extern Clock *clock;
    
    enum TetriminoStatus{MENULOOP, GAMELOOP, QUIT};
    extern TetriminoStatus tetriminoStatus;
    
    enum MenuHolderStatus{MAINMENU, STARTMENU, OPTIONMENU, QUITMENU};
    extern MenuHolderStatus menuHolderStatus;

    enum GameHolderStatus{AREDELAY, DROP, LOCKDELAY, LOCK, QUITGAME};
    extern GameHolderStatus gameHolderStatus;
    extern Uint32 areDelayTime;
    extern Uint32 lockDelayTime;
};

#endif

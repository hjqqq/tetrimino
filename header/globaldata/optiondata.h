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
    
    enum MenuHolderStatus{MAINMENU, OPTIONMENU, CONTROLMENU, QUITMENU};
    extern MenuHolderStatus menuHolderStatus;

    enum GameHolderStatus{START, AREDELAY, DROP, GAMEOVER, QUITGAME};
    extern GameHolderStatus gameHolderStatus;

    extern Uint32 dasDelayTime;
    
    extern Uint32 areDelayTime;
    extern Uint32 lockDelayTime;

    extern double horizontalSpeed;
    extern double normalDropSpeed;
    extern double softDropSpeed;

    enum RandomizerType{BAG, HISTORY4ROLL};
    extern RandomizerType randomizerType;
    extern int history4Roll[4];
    
    extern bool haveghost;
    extern bool haveholder;
};

#endif

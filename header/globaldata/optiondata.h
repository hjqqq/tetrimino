#ifndef OPTIONDATA_H
#define OPTIONDATA_H

#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "clock.h"
#include "playerdata.h"

/**
   @file optiondata.h
 */

/**
   游戏中可以通过菜单选项改变的，游戏运行时才被赋值的变量。
 */

namespace OptionData{
    enum TetriminoStatus{MENULOOP, GAMELOOP, QUIT};
    extern TetriminoStatus tetriminoStatus;
    
    enum MenuHolderStatus{MAINMENU, OPTIONMENU, PLAYERMENU, KEYSETMENU, QUITMENU};
    extern MenuHolderStatus menuHolderStatus;

    enum GameHolderStatus{READY, RUN, PAUSE, QUITGAME};
    extern GameHolderStatus gameHolderStatus;

    extern int minoPixSizeX;
    extern int minoPixSizeY;
    extern Vector2<int> minoPixSize;

    extern int areDelayTime;
    extern int lockDelayTime;
    
    extern int playerSize;
    extern PlayerData playerData1;
    extern PlayerData playerData2;    
    extern PlayerData playerData3;
    extern PlayerData playerData4;
    
    extern PlayerData *allPlayerData[StableData::playerSizeMax];
    
    extern int ghostAlpha;
    extern int musicVolume;
    extern int chunkVolume;
};

#endif

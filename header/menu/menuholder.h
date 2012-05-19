#ifndef MENUHOLDER_H
#define MENUHOLDER_H

/**
   @file menuholder.h
*/
#include <vector>
#include "SDL.h"
#include "menu.h"
#include "simplelabel.h"
#include "setting.h"

/**
   @brief 管理菜单，更新游戏变量。

   定义菜单，处理菜单事件，为内部的菜单添加项等
*/
class MenuHolder{
public:
    /**
       @brief 建立菜单，初始化游戏变量
    */
    MenuHolder();
    ~MenuHolder();

    /**
       处理事件

       @param event 传入的事件
    */
    void handleEvent(const SDL_Event &event);

    /**
       刷新display，blit菜单
    */
    void update();
    
private:
    Menu * mainMenu;
    Menu * optionMenu;
    Setting menu_setting;
/*    
    SimpleLabel * instructionLabel1;
    SimpleLabel * instructionLabel2;
    SimpleLabel * instructionLabel3;
*/ 
    std::vector<Menu*> playerMenuVector;
    std::vector<Menu*>::iterator playerMenuIter;
  
    std::vector<Menu*> keySetMenuVector;
    std::vector<Menu*>::iterator keySetMenuIter;
    
    void constructMainMenu();
    void constructOptionMenu();
    void constructPlayerMenu();
    void constructKeySetMenu();
    void selectPlayerMenu(const SDL_Event &);
};

#endif

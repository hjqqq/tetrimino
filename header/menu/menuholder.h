#ifndef MENUHOLDER_H
#define MENUHOLDER_H

#include "SDL.h"
#include "menu.h"

class MenuHolder{
public:
    MenuHolder();
    void handleEvent(const SDL_Event &event);
    void update();
    
private:
    void constructMainMenu();
    void constructStartMenu();
    void constructOptionMenu();

    Menu *mainMenu;
    Menu *startMenu;
    Menu *optionMenu;
};

#endif

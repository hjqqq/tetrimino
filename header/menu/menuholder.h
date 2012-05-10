#ifndef MENUHOLDER_H
#define MENUHOLDER_H

#include <vector>
#include "SDL.h"
#include "menu.h"

class MenuHolder{
 public:
  MenuHolder();
  ~MenuHolder();
  void handleEvent(const SDL_Event &event);
  void update();
    
 private:
  void constructMainMenu();
  void constructOptionMenu();
  void constructControlMenu();
  void selectControlMenu(const SDL_Event &);

  Menu * mainMenu;
  Menu * optionMenu;

  std::vector<Menu*> controlMenuVector;
  int currentMenuSelector;
};

#endif

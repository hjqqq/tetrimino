#ifndef MENUHOLDER_H
#define MENUHOLDER_H

#include <vector>
#include "SDL.h"
#include "menu.h"
#include "setting.h"

class MenuHolder{
 public:
  MenuHolder();
  ~MenuHolder();
  void handleEvent(const SDL_Event &event);
  void update();
    
 private:
  Menu * mainMenu;
  Menu * optionMenu;
  Setting menu_setting;

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

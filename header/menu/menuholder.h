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
  void constructPlayerMenu();
  void constructKeySetMenu();
  void selectPlayerMenu(const SDL_Event &);

  Menu * mainMenu;
  Menu * optionMenu;

  std::vector<Menu*> playerMenuVector;
  std::vector<Menu*>::iterator playerMenuIter;
  
  std::vector<Menu*> keySetMenuVector;
  std::vector<Menu*>::iterator keySetMenuIter;
};

#endif

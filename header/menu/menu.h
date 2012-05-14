#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>

#include "SDL.h"
#include "label.h"

class Menu : public Widget{
public:
    Menu(const Rect<int> &_rect);
    ~Menu();
    void addLabel(Label *label);
    void verticalLayout();

    virtual void handleEvent(const SDL_Event &event);
    virtual void update();

    virtual void setRect(const Rect<int> &newRect);
    
    void selectPrevious();
    void selectNext();
    int getSelect() const;
    void setSelect(int index);
    inline void resetSelect();
    
private:
    void handleKey(const SDLKey &sym);
    void updateSelect();
    SDL_Surface *menufg;
    std::string image_file;

    std::vector<Widget*> labelVector;
    int select;
};

void Menu::resetSelect()
{
  select = 0;
}
#endif

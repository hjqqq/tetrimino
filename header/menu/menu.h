#ifndef MENU_H
#define MENU_H

#include <vector>

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
    
private:
    void handleKey(const SDLKey &sym);
    void updateSelect();
    
    std::vector<Widget*> labelVector;
    int select;
};

#endif

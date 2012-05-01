#ifndef WIDGET_H
#define WIDGET_H

#include "action.h"
#include "rect.h"

class Widget{
public:
    Widget(const Rect<int> &_rect, Action *_action);
    virtual ~Widget();
    
    virtual void handleEvent(const SDL_Event &event);
    virtual void update();
    
    virtual const Rect<int> getRect() const;
    virtual void setRect(const Rect<int> &newRect);
protected:
    Rect<int> rect;
    Action *action;
};

#endif

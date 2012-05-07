#ifndef WIDGET_H
#define WIDGET_H

#include "action.h"
#include "rect.h"

class Widget{
 public:
  Widget(const Rect<int> &_rect);
  virtual ~Widget();
    
  virtual void handleEvent(const SDL_Event &event);
  virtual void update();
    
  virtual const Rect<int> getRect() const;
  virtual void setRect(const Rect<int> &newRect);
  inline void setAction(Action *);

 protected:
  Rect<int> rect;
  Action *action;
    
  inline virtual void act();
};

void Widget::setAction(Action *_action)
{ 
  delete action;
  action = _action;
}

void Widget::act()
{
  if(action != NULL) 
    (*action)();
}
#endif

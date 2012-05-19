#ifndef WIDGET_H
#define WIDGET_H

#include "action.h"
#include "rect.h"

/**
   @file widget.h
*/

/**
   @brief 所有label的基类

   处理自己的事件，把自己blit到屏幕上
*/
class Widget{
public:
    /**
       @param _rect 传入一个Rect<int>的对象，用来决定把自己blit到屏幕上的位置
    */
    Widget(const Rect<int> &_rect);
    virtual ~Widget();

    /**
       @param event 根据传入的event，处理对自己的事件
     */
    virtual void handleEvent(const SDL_Event &event);

    /**
       把自己blit到屏幕上去
     */
    virtual void update();

    /**
       @return Rect<int> 返回保存的rect对象Rect<int>
     */
    virtual const Rect<int> getRect() const;

    /**
       @param newRect 更改保存的rect
     */
    virtual void setRect(const Rect<int> &newRect);
    
    /**
       绑定Action，决定每个Widget的行为
       @param  action 传入Action或其子类的指针，并管理传入指针对应的内存
     */
    inline void setAction(Action * action);

protected:
    
    /**
       保存blit的位置
     */
    Rect<int> rect;

    /**
       保存绑定的Action或子类对象的指针
     */
    Action *action;
    
    /**
       执行action
     */
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

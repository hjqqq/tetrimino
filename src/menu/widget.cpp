#include <iostream>
#include "widget.h"

Widget::Widget(const Rect<int> &_rect):
    rect(_rect),action(NULL)
{}

Widget::~Widget()
{
    delete action;
}

void Widget::handleEvent(const SDL_Event &event)
{}

void Widget::update()
{}

const Rect<int> Widget::getRect() const
{
    return rect;
}

void Widget::setRect(const Rect<int> &newRect)
{
    rect = newRect;
}

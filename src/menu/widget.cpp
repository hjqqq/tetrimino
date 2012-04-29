#include <iostream>
#include "widget.h"

Widget::Widget(const Rect &_rect, Action *_action):
    rect(_rect), action(_action)
{}

Widget::~Widget()
{
    delete action;
}

void Widget::handleEvent(const SDL_Event &event)
{}

void Widget::update()
{}

const Rect Widget::getRect() const
{
    return rect;
}

void Widget::setRect(const Rect &newRect)
{
    rect = newRect;
}

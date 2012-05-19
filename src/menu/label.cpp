#include <iostream>
#include <SDL_ttf.h>

#include "stabledata.h"
#include "optiondata.h"
#include "label.h"
#include "utility.h"

Label::Label(const Rect<int> &_rect,
	     const std::string &_text,
	     const SDL_Color &_color):
    Widget(_rect),
    text(_text), color(_color), labelSurface(NULL)
{}

Label::~Label()
{}

void Label::setColor(const SDL_Color &newColor)
{
    color = newColor;
}

void Label::setText(const std::string &newText)
{
    text = newText;
}

void Label::setRect(const Rect<int> &newRect)
{
    rect = newRect;
    destroyLabelSurface();
    constructLabelSurface();
}

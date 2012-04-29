#include <iostream>
#include <SDL_ttf.h>

#include "stabledata.h"
#include "optiondata.h"
#include "label.h"
#include "utility.h"

Label::Label(const Rect &_rect,
	     Action *_action,
	     const std::string &_text,
	     const SDL_Color &_color):
    Widget(_rect, _action),
    text(_text), color(_color), labelSurface(NULL)
{
    constructLabelSurface();
}

Label::~Label()
{
    destroyLabelSurface();
}

void Label::handleEvent(const SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN &&
	event.key.keysym.sym == SDLK_RETURN){
	std::cerr << "haha\n";
	(*action)();
    }
}

void Label::update()
{
    SDL_BlitSurface(labelSurface, &srcrect, 
		    OptionData::display, &dstrect);
}

void Label::setColor(const SDL_Color &newColor)
{
    color = newColor;
}

void Label::setText(const std::string &newText)
{
    text = newText;
}

void Label::constructLabelSurface()
{
    labelSurface = TTF_RenderText_Solid(
	OptionData::font, text.c_str(), color);
    Rect blitRect(get_rect(labelSurface));
    blitRect.setCenter(rect.getCenter());
    blitRect.clipRect(rect);
    
    srcrect = Rect(Vector2(), blitRect.diagonal).getSDL_Rect();
    dstrect = Rect(blitRect.pos, Vector2()).getSDL_Rect();
}

void Label::destroyLabelSurface()
{
    SDL_FreeSurface(labelSurface);
}

void Label::setRect(const Rect &newRect)
{
    rect = newRect;
    destroyLabelSurface();
    constructLabelSurface();
}

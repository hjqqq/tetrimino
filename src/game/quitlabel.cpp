#include <iostream>
#include <string>

#include "quitlabel.h"
#include "optiondata.h"
#include "utility.h"

QuitLabel::QuitLabel(const Rect<int> &_rect,
		     const std::string &_text,
		     const SDL_Color &_color,
		     bool _toggle,
    		     const std::string &_help):
    Label(_rect,  _text, _help,  _color), toggle(_toggle)
{
    constructLabelSurface();
}

QuitLabel::~QuitLabel()
{
    destroyLabelSurface();
}

void QuitLabel::handleEvent(const SDL_Event &event)
{
    if(event.type == SDL_KEYDOWN){
	switch (event.key.keysym.sym) {
	case SDLK_LEFT:	case SDLK_RIGHT:
	    toggle ^= 1;
	    destroyLabelSurface();
	    constructLabelSurface();	    
	    break;
	}
    }
}

void QuitLabel::update()
{
    SDL_BlitSurface(labelSurface, &srcrect,
		    ResourceData::display, &dstrect);
}

void QuitLabel::constructLabelSurface()
{
    std::string textWithToggle = toggle? (text + " Yes"): (text + " No");
    
    labelSurface = TTF_RenderText_Blended(
	ResourceData::font, textWithToggle.c_str(), color);
    Rect<int> blitRect(get_rect(labelSurface));
    blitRect.setCenter(rect.getCenter());
    blitRect.clipRect(rect);
    
    srcrect = Rect<int>(Vector2<int>(), blitRect.diagonal).getSDL_Rect();
    dstrect = Rect<int>(blitRect.pos, Vector2<int>()).getSDL_Rect();
}

void QuitLabel::destroyLabelSurface()
{
    SDL_FreeSurface(labelSurface);
}

void QuitLabel::act()
{
    if(action != NULL){
	(*action)(toggle);
    }
}

bool QuitLabel::getToggle()
{
    return toggle;
}

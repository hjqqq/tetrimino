#include <iostream>
#include <string>
#include "togglelabel.h"
#include "optiondata.h"
#include "utility.h"

ToggleLabel::ToggleLabel(const Rect<int> &_rect,
			 const std::string &_text,
			 const bool &_toggle,
			 const std::string &_help,
			 const SDL_Color &_color ):
    Label(_rect,  _text, _help, _color), toggle(_toggle)
{
    freshToggleText();
    constructLabelSurface();
}

ToggleLabel::~ToggleLabel()
{
    destroyLabelSurface();
}

void ToggleLabel::handleEvent(const SDL_Event &event)
{
    if(event.type == SDL_KEYDOWN)
	switch (event.key.keysym.sym) {
	case SDLK_RETURN:
	    act();
	    freshToggleText();
	    destroyLabelSurface();
	    constructLabelSurface();
	    break;
	}
}

void ToggleLabel::update()
{
    SDL_BlitSurface(labelSurface, &srcrect,
		    ResourceData::display, &dstrect);
}

void ToggleLabel::letsToggle()
{
    if (toggle == true)
	toggle = false;
    else
	toggle = true;
}

void ToggleLabel::constructLabelSurface()
{
    labelSurface = TTF_RenderText_Blended(
	ResourceData::font, toggle_text.c_str(), color);
    Rect<int> blitRect(get_rect(labelSurface));
    blitRect.setCenter(rect.getCenter());
    blitRect.clipRect(rect);
    
    srcrect = Rect<int>(Vector2<int>(), blitRect.diagonal).getSDL_Rect();
    dstrect = Rect<int>(blitRect.pos, Vector2<int>()).getSDL_Rect();
}

void ToggleLabel::destroyLabelSurface()
{
    SDL_FreeSurface(labelSurface);
}

void ToggleLabel::freshToggleText()
{
    if( toggle == true )
	toggle_text = text + " : yes";
    else
	toggle_text = text + " : no";
}

void ToggleLabel::act()
{
    if(action != NULL){
	letsToggle();
	(*action)(toggle);
    }
}

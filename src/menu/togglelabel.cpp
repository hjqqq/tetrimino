#include <iostream>
#include <string>
#include "togglelabel.h"
#include "optiondata.h"
#include "utility.h"

ToggleLabel::ToggleLabel(const Rect<int> &_rect,
			 const std::string &_text,
			 const SDL_Color &_color,
			 bool _toggle):
  Label(_rect,  _text, _color), toggle(_toggle)
{
  freshToggleText();
  destroyLabelSurface();
  constructLabelSurface();
}

ToggleLabel::~ToggleLabel()
{}

void ToggleLabel::handleEvent(const SDL_Event &event)
{
  if(event.type == SDL_KEYDOWN)
    switch (event.key.keysym.sym) {
    case SDLK_RETURN:
      letsToggle();
      act();
      break;
    }
}

void ToggleLabel::update()
{
  freshToggleText();
  destroyLabelSurface();
  constructLabelSurface();
  SDL_BlitSurface(labelSurface, &srcrect,
		  OptionData::display, &dstrect);
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
  labelSurface = TTF_RenderText_Solid(
				      OptionData::font, toggle_text.c_str(), color);
  Rect<int> blitRect(get_rect(labelSurface));
  blitRect.setCenter(rect.getCenter());
  blitRect.clipRect(rect);
    
  srcrect = Rect<int>(Vector2<int>(), blitRect.diagonal).getSDL_Rect();
  dstrect = Rect<int>(blitRect.pos, Vector2<int>()).getSDL_Rect();
}

void ToggleLabel::freshToggleText()
{
  if( toggle == true )
    toggle_text = text + " : on";
  else
    toggle_text = text + " : off";
}

void ToggleLabel::act()
{
  if(action != NULL)
    (*action)(toggle);
}

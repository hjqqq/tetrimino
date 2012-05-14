#include <iostream>
#include <SDL_ttf.h>

#include "stabledata.h"
#include "optiondata.h"
#include "simplelabel.h"
#include "utility.h"

SimpleLabel::SimpleLabel(const Rect<int> &_rect,
			 const std::string &_text,
			 const SDL_Color &_color):
  Label(_rect, _text, _color)
{
  constructLabelSurface();
}

SimpleLabel::~SimpleLabel()
{
  destroyLabelSurface();
}

void SimpleLabel::handleEvent(const SDL_Event &event)
{
  if (event.type == SDL_KEYDOWN &&
      event.key.keysym.sym == SDLK_RETURN){
    act();
  }
}

void SimpleLabel::update()
{
  SDL_BlitSurface(labelSurface, &srcrect, 
		  ResourceData::display, &dstrect);
}

void SimpleLabel::constructLabelSurface()
{
  labelSurface = TTF_RenderText_Blended(
				      ResourceData::font, text.c_str(), color);
  Rect<int> blitRect(get_rect(labelSurface));
  blitRect.setCenter(rect.getCenter());
  blitRect.clipRect(rect);
    
  srcrect = Rect<int>(Vector2<int>(), blitRect.diagonal).getSDL_Rect();
  dstrect = Rect<int>(blitRect.pos, Vector2<int>()).getSDL_Rect();
}

void SimpleLabel::destroyLabelSurface()
{
  SDL_FreeSurface(labelSurface);
}

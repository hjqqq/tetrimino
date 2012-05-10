#include <string>
#include <iostream>
#include "utility.h"
#include "optiondata.h"
#include "playerdata.h"
#include "keysetlabel.h"

KeySetLabel::KeySetLabel(
			 const Rect<int> &_rect,
			 const std::string &_text,
			 const SDLKey &_key,
			 const SDL_Color &_color) :
  Label(_rect, _text, _color), key(_key),
  default_key(_key)
{
  freshShowText();
  destroyLabelSurface();
  constructLabelSurface();
}

KeySetLabel::~KeySetLabel()
{}

void KeySetLabel::handleEvent( const SDL_Event &event)
{
  if( event.type == SDL_KEYDOWN )
    if( event.key.keysym.sym == SDLK_RETURN ){
	getUserInput();
    }else if( event.key.keysym.sym == SDLK_r )
      key = default_key;
}

void KeySetLabel::getUserInput()
{
  SDL_Event event;
  while(true)
    {
      SDL_WaitEvent(&event);
      
      if( (event.type == SDL_KEYDOWN) &&
	  (strcmp(SDL_GetKeyName(event.key.keysym.sym), "unknown key") != 0) )
	{
	  key = event.key.keysym.sym;
	  act();
	  break;
	}
    }
}

void KeySetLabel::update()
{
  freshShowText();
  destroyLabelSurface();
  constructLabelSurface();
  SDL_BlitSurface(labelSurface, &srcrect,
		  OptionData::display, &dstrect);
}

void KeySetLabel::constructLabelSurface()
{
  labelSurface = TTF_RenderText_Solid(
				      OptionData::font, show_text.c_str(), color);
  Rect<int> blitRect(get_rect(labelSurface));
  blitRect.setCenter(rect.getCenter());
  blitRect.clipRect(rect);
    
  srcrect = Rect<int>(Vector2<int>(), blitRect.diagonal).getSDL_Rect();
  dstrect = Rect<int>(blitRect.pos, Vector2<int>()).getSDL_Rect();
}

void KeySetLabel::act()
{
  if( action != NULL)
    (*action)((double)key);
  std::cout << "playerdata: " << SDL_GetKeyName(playerData1.hardDrop) << std::endl;
}

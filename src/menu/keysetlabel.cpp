#include <string>
#include "color.h"
#include "utility.h"
#include "optiondata.h"
#include "playerdata.h"
#include "keysetlabel.h"

KeySetLabel::KeySetLabel(
    const Rect<int> &_rect,
    const std::string &_text,
    const SDLKey &_key,
    const std::string &_help,
    const SDL_Color &_color) :
    Label(_rect, _text, _help, _color), key(_key),
    default_key(_key)
{
    freshShowText();
    constructLabelSurface();
}

KeySetLabel::~KeySetLabel()
{
    destroyLabelSurface();
}

void KeySetLabel::handleEvent( const SDL_Event &event)
{ 
    if( event.type == SDL_KEYDOWN ){
	if( event.key.keysym.sym == SDLK_RETURN )
	    color = red;
	else if( event.key.keysym.sym == SDLK_r )
	    key = default_key;
    }else if( event.key.keysym.sym == SDLK_RETURN ){
	getUserInput();
    }
    freshShowText();
    destroyLabelSurface();
    constructLabelSurface();
}

void KeySetLabel::getUserInput()
{
    SDL_Event event;
    while(true)
    {
	SDL_WaitEvent(&event);
      
	if( (event.type == SDL_KEYUP) &&
	    (strcmp(SDL_GetKeyName(event.key.keysym.sym), "unknown key") != 0) )
	{
	    key = event.key.keysym.sym;
	    act();
	    break;
	}
	else if( event.type == SDL_QUIT ) {
	    OptionData::menuHolderStatus = OptionData::QUITMENU;
	    break;
	}
    }
    color = black;
}

void KeySetLabel::update()
{
    SDL_BlitSurface(labelSurface, &srcrect,
		    ResourceData::display, &dstrect);
}

void KeySetLabel::constructLabelSurface()
{
    labelSurface = TTF_RenderText_Blended(
	ResourceData::font, show_text.c_str(), color);
    Rect<int> blitRect(get_rect(labelSurface));
    blitRect.setCenter(rect.getCenter());
    blitRect.clipRect(rect);
    
    srcrect = Rect<int>(Vector2<int>(), blitRect.diagonal).getSDL_Rect();
    dstrect = Rect<int>(blitRect.pos, Vector2<int>()).getSDL_Rect();
}

void KeySetLabel::destroyLabelSurface()
{
    SDL_FreeSurface(labelSurface);
}

void KeySetLabel::act()
{
    if( action != NULL)
	(*action)((double)key);
}

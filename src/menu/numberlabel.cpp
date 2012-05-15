#include <string>
#include "numberlabel.h"
#include "resourcedata.h"

NumberLabel::NumberLabel(const Rect<int> &_rect,
			 const std::string &_text,
			 const std::string &_unit,
			 const double &_number,
			 const double &_min_number,
			 const double &_max_number,
			 const double &_plus_factor,
			 const SDL_Color &_color) :
    Label(_rect, _text, _color), number(_number), 
    default_number(_number), UNIT(_unit), 
    PLUS_FACTOR(_plus_factor),
    MIN_NUMBER(_min_number),
    MAX_NUMBER(_max_number)
{
    SDL_EnableUNICODE(SDL_ENABLE);
    input_state = false;

    syncToNumberText();
    freshShowText();
  
    constructLabelSurface();
}

NumberLabel::~NumberLabel()
{  
    destroyLabelSurface();
    SDL_EnableUNICODE(SDL_DISABLE);
}

void NumberLabel::handleEvent( const SDL_Event &event)
{
    if( event.type == SDL_KEYDOWN ) {
	if (event.key.keysym.sym == SDLK_RETURN ){
	    toggleInputState();
	}
	else if(input_state == true)
	    getUserInput(event);
	else 
	    switch(event.key.keysym.sym){
	    case SDLK_r: 
		reset(); 
		break;
	    case SDLK_MINUS:
		if( (number -= PLUS_FACTOR) <= MIN_NUMBER)
		    number = MIN_NUMBER;;
		syncToNumberText();
		act();
		break;
	    case SDLK_EQUALS:
		if( (number += PLUS_FACTOR) >= MAX_NUMBER)
		    number = MAX_NUMBER;
		syncToNumberText();
		act();
		break;
	    }
	freshShowText();
	destroyLabelSurface();
	constructLabelSurface();
    }
}

void NumberLabel::update()
{
    SDL_BlitSurface(labelSurface, &srcrect,
		    ResourceData::display, &dstrect);
}

void NumberLabel::getUserInput(const SDL_Event &event)
{

    if( (event.key.keysym.unicode >= (Uint16)'0') &&
	(event.key.keysym.unicode <= (Uint16)'9') )
	number_text += (char)event.key.keysym.unicode;
  
    if( event.key.keysym.unicode == (Uint16)'.' )
	number_text += (char)event.key.keysym.unicode;


    if( (event.key.keysym.sym == SDLK_BACKSPACE) &&
	(number_text.length() != 0) ){
	number_text.erase( number_text.length() - 1);
    }
}

void NumberLabel::constructLabelSurface()
{
    labelSurface = TTF_RenderText_Blended(
	ResourceData::font, show_text.c_str(), color);
    Rect<int> blitRect(get_rect(labelSurface));
    blitRect.setCenter(rect.getCenter());
    blitRect.clipRect(rect);
    
    srcrect = Rect<int>(Vector2<int>(), blitRect.diagonal).getSDL_Rect();
    dstrect = Rect<int>(blitRect.pos, Vector2<int>()).getSDL_Rect();
}

void NumberLabel::destroyLabelSurface()
{
    SDL_FreeSurface(labelSurface);
}
void NumberLabel::toggleInputState()
{
    if (input_state == true) {
	input_state = false;
	if ( (number_text.length() == 0) || 
	     (atof(number_text.c_str()) < MIN_NUMBER ) ||
	     (atof(number_text.c_str()) > MAX_NUMBER) )
	    syncToNumberText();
	else
	    syncToNumber();
	act();
    }
    else{
	input_state = true;
	number_text = "";
    }
}

void NumberLabel::reset()
{
    number = default_number;
    syncToNumberText();
    act();
}

void NumberLabel::act()
{
    if(action != NULL)
	(*action)(number);
}

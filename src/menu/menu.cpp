#include <iostream>
#include <string>
#include "menu.h"
#include "resourcedata.h"
#include "color.h"
#include "utility.h"
#include "sound.h"

Menu::Menu(const Rect<int> &_rect):
    Widget(_rect), select(0)
{
    image_file = "res/menufg.png";
    menufg = image_load_alpha(image_file.c_str());
}

Menu::~Menu()
{
    SDL_FreeSurface(menufg);
    for (int i = 0; i != labelVector.size(); ++i){
	delete labelVector[i];
    }
}

void Menu::addLabel(Label *label)
{
    labelVector.push_back(label);
    verticalLayout();
}

void Menu::verticalLayout()
{
    Vector2<int> topLeftPos(rect.pos);
    const Vector2<int> topLeftStep =
	Vector2<int>(0, rect.diagonal.y) / (int)labelVector.size();
    
    for (int i = 0; i != labelVector.size(); ++i){
	Rect<int> labelRect = labelVector[i]->getRect();
	labelRect.setTopLeft(topLeftPos);
	labelVector[i]->setRect(labelRect);
	topLeftPos += topLeftStep;
    }
}

void Menu::handleEvent(const SDL_Event &event)
{
    labelVector[select]->handleEvent(event);
    if ( OptionData::numberInputState == false )
	if ( event.type == SDL_KEYDOWN )
	    handleKey(event.key.keysym.sym);
}

void Menu::handleKey(const SDLKey &sym)
{
    switch (sym){
    case SDLK_UP:
	ResourceData::sound->playChunk(Sound::CURSOR);
	selectPrevious();
	break;
    case SDLK_DOWN:
	ResourceData::sound->playChunk(Sound::CURSOR);	
	selectNext();
	break;
    }
}

void Menu::update()
{
    updateSelect();
    for (int i = 0; i != labelVector.size(); ++i){
	labelVector[i]->update();
    }
}

void Menu::updateSelect()
{
    SDL_Rect dstrect = labelVector[select]->getRect().getSDL_Rect();
    SDL_Rect srcrect = {0, 0, dstrect.w, dstrect.h};
    SDL_BlitSurface(menufg, &srcrect, ResourceData::display, &dstrect);
}

void Menu::setRect(const Rect<int> &newRect)
{
    rect = newRect;
    verticalLayout();
}
    
void Menu::selectPrevious()
{
    if (select != 0)
	--select;
}

void Menu::selectNext()
{
    if (select < labelVector.size() - 1)
	++select;
}

int Menu::getSelect() const
{
    return select;
}

void Menu::setSelect(int index)
{
    select = index;
}


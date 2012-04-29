#include <iostream>
#include "SDL_draw.h"
#include "menu.h"
#include "optiondata.h"
#include "color.h"

Menu::Menu(const Rect &_rect, Action *_action):
    Widget(_rect, _action), select(0)
{
    verticalLayout();
}

Menu::~Menu()
{
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
    Vector2 topLeftPos(rect.pos);
    const Vector2 topLeftStep =
	Vector2(0, rect.diagonal.y) / labelVector.size();
    
    for (int i = 0; i != labelVector.size(); ++i){
	Rect labelRect = labelVector[i]->getRect();
	labelRect.setTopLeft(topLeftPos);
	labelVector[i]->setRect(labelRect);
	topLeftPos += topLeftStep;
    }
}

void Menu::handleEvent(const SDL_Event &event)
{
    switch (event.type){
    case SDL_KEYDOWN:
	handleKey(event.key.keysym.sym);
	break;
    }
    labelVector[select]->handleEvent(event);
}

void Menu::handleKey(const SDLKey &sym)
{
    switch (sym){
    case SDLK_UP:
	selectPrevious();
	break;
    case SDLK_DOWN:
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
    Uint32 color = SDL_MapRGB(OptionData::display->format, black.r, black.g, black.b);
    Draw_Round(OptionData::display, dstrect.x, dstrect.y, dstrect.w, dstrect.h, 50, color);
}

void Menu::setRect(const Rect &newRect)
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




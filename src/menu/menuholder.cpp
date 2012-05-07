#include "valuesetter.h"
#include "menuholder.h"
#include "stabledata.h"
#include "optiondata.h"
#include "togglelabel.h"
#include "togglesetter.h"

MenuHolder::MenuHolder()
{
  constructMainMenu();
  constructOptionMenu();
}

MenuHolder::~MenuHolder()
{
  delete mainMenu;
  delete optionMenu;
}

void MenuHolder::handleEvent(const SDL_Event &event)
{
  if (event.key.keysym.sym == SDLK_ESCAPE)
    OptionData::menuHolderStatus = OptionData::MAINMENU;
	    
  switch (OptionData::menuHolderStatus){
  case OptionData::MAINMENU:
    mainMenu->handleEvent(event);
    break;
  case OptionData::OPTIONMENU:
    optionMenu->handleEvent(event);
    break;
  }
}

void MenuHolder::update()
{
  switch (OptionData::menuHolderStatus){
  case OptionData::MAINMENU:
    mainMenu->update();
    break;
  case OptionData::OPTIONMENU:
    optionMenu->update();
    break;
  }
}

void MenuHolder::constructMainMenu(){
  ValueSetter <OptionData::MenuHolderStatus> *v1= 
    new ValueSetter<OptionData::MenuHolderStatus>(
						  OptionData::menuHolderStatus,
						  OptionData::OPTIONMENU);
  ValueSetter<OptionData::MenuHolderStatus> *v2 = 
    new ValueSetter<OptionData::MenuHolderStatus>(
						  OptionData::menuHolderStatus,
						  OptionData::QUITMENU);

  Label *optionLabel = new Label(
				 Rect<int>(0, 0, 200, 50),
				 "option");
  optionLabel->setAction(v1);
  
  Label *quitLabel = new Label(
			       Rect<int>(0, 0, 200, 50),
			       "quit");
  quitLabel->setAction(v2);

  mainMenu = new Menu(StableData::menuRect);
  mainMenu->addLabel(optionLabel);
  mainMenu->addLabel(quitLabel);
}

void MenuHolder::constructOptionMenu(){

  ToggleSetter *toggleGhostSetter = new ToggleSetter(OptionData::haveghost);
  ToggleSetter *toggleHolderSetter = new ToggleSetter(OptionData::haveholder);
  
  ToggleLabel *toggleGhostLabel = 
    new ToggleLabel(Rect<int>(0,0,200,50),
		    "Ghost");
  toggleGhostLabel->setAction(toggleGhostSetter);
  
  ToggleLabel *toggleHolderLabel =
    new ToggleLabel(Rect<int>(0,0,200,50),
		    "Holder");
  toggleHolderLabel->setAction(toggleHolderSetter);

  optionMenu = new Menu(StableData::menuRect);
  optionMenu->addLabel(toggleGhostLabel);
  optionMenu->addLabel(toggleHolderLabel);
}

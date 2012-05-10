#include <vector>
#include <iostream>
#include "valuesetter.h"
#include "menuholder.h"
#include "stabledata.h"
#include "optiondata.h"
#include "playerdata.h"
#include "togglelabel.h"
#include "togglesetter.h"
#include "numberlabel.h"
#include "numbersetter.h"
#include "keysetlabel.h"

MenuHolder::MenuHolder() : 
  currentMenuSelector(0)
{

  constructMainMenu();
  constructOptionMenu();
  constructControlMenu();
}

MenuHolder::~MenuHolder()
{
  delete mainMenu;
  delete optionMenu;
}

void MenuHolder::handleEvent(const SDL_Event &event)
{
  if ( (event.type == SDL_KEYDOWN) &&
       (event.key.keysym.sym == SDLK_ESCAPE) &&
       (OptionData::menuHolderStatus != OptionData::MAINMENU) )
    {
      OptionData::menuHolderStatus = 
	(OptionData::MenuHolderStatus) (OptionData::menuHolderStatus - 1);
    }
	    
  switch (OptionData::menuHolderStatus){
  case OptionData::MAINMENU:
    optionMenu->resetSelect();
    mainMenu->handleEvent(event);
    break;
  case OptionData::OPTIONMENU:
    currentMenuSelector = 0;
    optionMenu->handleEvent(event);
    break;
  case OptionData::CONTROLMENU:
    selectControlMenu(event);
    controlMenuVector[currentMenuSelector]->handleEvent(event);
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
  case OptionData::CONTROLMENU:
    controlMenuVector[currentMenuSelector]->update();
    break;
  }
}

void MenuHolder::constructMainMenu()
{
  ValueSetter <OptionData::MenuHolderStatus> *v1= 
    new ValueSetter<OptionData::MenuHolderStatus>(
						  OptionData::menuHolderStatus,
						  OptionData::OPTIONMENU);
  Label *optionLabel = new Label( Rect<int>(0, 0, 400, 50), "option");
  optionLabel->setAction(v1);

  ValueSetter<OptionData::MenuHolderStatus> *v2 = 
    new ValueSetter<OptionData::MenuHolderStatus>(
						  OptionData::menuHolderStatus,
						  OptionData::QUITMENU);
  Label *quitLabel = new Label( Rect<int>(0, 0, 400, 50), "quit");
  quitLabel->setAction(v2);

  mainMenu = new Menu(StableData::menuRect);
  mainMenu->addLabel(optionLabel);
  mainMenu->addLabel(quitLabel);
}

void MenuHolder::constructOptionMenu()
{
  ValueSetter<OptionData::MenuHolderStatus> *controlSetter = 
    new ValueSetter<OptionData::MenuHolderStatus>(
						  OptionData::menuHolderStatus,
						  OptionData::CONTROLMENU);
  Label *controlLabel = new Label( Rect<int>(0, 0, 400, 50), "Set Keyboard Control");
  controlLabel->setAction(controlSetter);

  ToggleSetter *toggleGhostSetter = new ToggleSetter(OptionData::haveghost);
  ToggleLabel *toggleGhostLabel = 
    new ToggleLabel(Rect<int>(0,0,400,50),
		    "Ghost");
  toggleGhostLabel->setAction(toggleGhostSetter);

  ToggleSetter *toggleHolderSetter = new ToggleSetter(OptionData::haveholder);  
  ToggleLabel *toggleHolderLabel =
    new ToggleLabel(Rect<int>(0,0,400,50),
		    "Holder");
  toggleHolderLabel->setAction(toggleHolderSetter);

  NumberSetter<double> *normalDropSpeedSetter = new NumberSetter<double>(OptionData::normalDropSpeed);
  NumberLabel *normalDropSpeedLabel=
    new NumberLabel(Rect<int>(0,0,400,50),
		    "normalDropSpeed", "G", 0.05,
		    OptionData::normalDropSpeed);
  normalDropSpeedLabel->setAction(normalDropSpeedSetter);

  NumberSetter<double> *softDropSpeedSetter = new NumberSetter<double>(OptionData::softDropSpeed);
  NumberLabel *softDropSpeedLabel=
    new NumberLabel(Rect<int>(0,0,400,50),
		    "softDropSpeed", "G", 0.05,
		    OptionData::softDropSpeed);
  softDropSpeedLabel->setAction(softDropSpeedSetter);

  NumberSetter<double> *horizontalSpeedSetter = 
    new NumberSetter<double>(OptionData::horizontalSpeed);
  NumberLabel *horizontalSpeedLabel =
    new NumberLabel(Rect<int>(0,0,400,50),
		    "HorizontalSpeed", "G", 0.05,
		    OptionData::horizontalSpeed);
  horizontalSpeedLabel->setAction(horizontalSpeedSetter);

  NumberSetter<Uint32> *dasDelayTimeSetter = 
    new NumberSetter<Uint32>(OptionData::dasDelayTime);
  NumberLabel *dasDelayTimeLabel =
    new NumberLabel(Rect<int>(0,0,400,50),
		    "DAS delay time", "ms", 100,
		    (double) OptionData::dasDelayTime);
  dasDelayTimeLabel->setAction(dasDelayTimeSetter);

  optionMenu = new Menu(StableData::menuRect);
  optionMenu->addLabel(toggleGhostLabel);
  optionMenu->addLabel(toggleHolderLabel);

  optionMenu->addLabel(horizontalSpeedLabel);
  optionMenu->addLabel(normalDropSpeedLabel);
  optionMenu->addLabel(softDropSpeedLabel);

  optionMenu->addLabel(dasDelayTimeLabel);

  optionMenu->addLabel(controlLabel);
}

void MenuHolder::constructControlMenu()
{
  Label * control1pLabel = new Label( Rect<int>(0, 0, 400, 50), "1p");
  NumberSetter<SDLKey> *hardDropSetter = 
    new NumberSetter<SDLKey>(playerData1.hardDrop);
  KeySetLabel * hardDropLabel = new KeySetLabel( 
						Rect<int>(0,0,400,50),
						"Hard Drop",
						playerData1.hardDrop);
  hardDropLabel->setAction(hardDropSetter);
  Menu * control1pMenu = new Menu(StableData::menuRect);
  control1pMenu->addLabel(control1pLabel);
  control1pMenu->addLabel(hardDropLabel);

  Label * control2pLabel = new Label( Rect<int>(0,0,400,50), "2p");
  Menu * control2pMenu = new Menu(StableData::menuRect);
  control2pMenu->addLabel(control2pLabel);

  Label * control3pLabel = new Label( Rect<int>(0,0,400,50), "3p");
  Menu * control3pMenu = new Menu(StableData::menuRect);
  control3pMenu->addLabel(control3pLabel);

  Label * control4pLabel = new Label( Rect<int>(0,0,400,50), "4p");
  Menu * control4pMenu = new Menu(StableData::menuRect);
  control4pMenu->addLabel(control4pLabel);
  
  controlMenuVector.push_back(control1pMenu);
  controlMenuVector.push_back(control2pMenu);
  controlMenuVector.push_back(control3pMenu);
  controlMenuVector.push_back(control4pMenu);
}

void MenuHolder::selectControlMenu(const SDL_Event & event)
{
  if( event.type == SDL_KEYDOWN )
    switch( event.key.keysym.sym )
      {
      case SDLK_RIGHT:
	if(currentMenuSelector < controlMenuVector.size() - 1 )
	  ++currentMenuSelector;
	break;
      case SDLK_LEFT:
	if( currentMenuSelector > 0 ) 
	  --currentMenuSelector;
      }
}

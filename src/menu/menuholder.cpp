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
using namespace std;

MenuHolder::MenuHolder()
{
  constructMainMenu();
  constructOptionMenu();
  constructPlayerMenu();
  constructKeySetMenu();
  playerMenuIter = playerMenuVector.begin();
  keySetMenuIter = keySetMenuVector.begin();
}

MenuHolder::~MenuHolder()
{
  delete mainMenu;
  delete optionMenu;
  for (std::vector<Menu*>::iterator iter = playerMenuVector.begin(); 
       iter != playerMenuVector.end(); 
       ++iter ) 
    {
      delete(*iter);
    }
  for (std::vector<Menu*>::iterator iter = keySetMenuVector.begin(); 
       iter != keySetMenuVector.end(); 
       ++iter ) 
    {
      delete(*iter);
    }
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
    mainMenu->handleEvent(event);
    break;
  case OptionData::OPTIONMENU:
    optionMenu->handleEvent(event);
    break;
  case OptionData::PLAYERMENU:
    selectPlayerMenu(event);
    (*playerMenuIter)->handleEvent(event);
    break;
  case OptionData::KEYSETMENU:
    (*keySetMenuIter)->handleEvent(event);
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
  case OptionData::PLAYERMENU:
    (*playerMenuIter)->update();
    break;
  case OptionData::KEYSETMENU:
    (*keySetMenuIter)->update();
  }
}

void MenuHolder::constructMainMenu()
{
  // labels
  SimpleLabel *startLabel = new SimpleLabel( Rect<int>(0, 0, 400, 50), "START");
  SimpleLabel *optionLabel = new SimpleLabel( Rect<int>(0, 0, 400, 50), "OPTION");
  SimpleLabel *aboutLabel = new SimpleLabel( Rect<int>(0, 0, 400, 50), "ABOUT");
  SimpleLabel *quitLabel = new SimpleLabel( Rect<int>(0, 0, 400, 50), "QUIT");

  // setters
  ValueSetter <OptionData::MenuHolderStatus> *optionSetter= 
    new ValueSetter<OptionData::MenuHolderStatus>(
						  OptionData::menuHolderStatus,
						  OptionData::OPTIONMENU);
  ValueSetter<OptionData::MenuHolderStatus> *quitSetter = 
    new ValueSetter<OptionData::MenuHolderStatus>(
						  OptionData::menuHolderStatus,
						  OptionData::QUITMENU);

  // combine setters & labels
  optionLabel->setAction(optionSetter);
  quitLabel->setAction(quitSetter);

  // construct and setup menu
  mainMenu = new Menu(StableData::menuRect);
  mainMenu->addLabel(startLabel);
  mainMenu->addLabel(optionLabel);
  mainMenu->addLabel(aboutLabel);
  mainMenu->addLabel(quitLabel);
}

void MenuHolder::constructOptionMenu()
{
  /******************************* labels **********************************/
  
  SimpleLabel *playerLabel = new SimpleLabel( Rect<int>(0, 0, 400, 50), "Player Setting");
  
  /****************************** setters *********************************/
  ValueSetter<OptionData::MenuHolderStatus> *playerSetter = 
    new ValueSetter<OptionData::MenuHolderStatus>(
						  OptionData::menuHolderStatus,
						  OptionData::PLAYERMENU);

  /*********************** combine setters & labels **************************/
  playerLabel->setAction(playerSetter);

  /********************** construct menu & setup menu ***********************/
  optionMenu = new Menu(StableData::menuRect);
  optionMenu->addLabel(playerLabel);
}

void MenuHolder::constructPlayerMenu()
{
  /******************************** labels ************************************/
  SimpleLabel * player1pLabel = new SimpleLabel( Rect<int>(0,0,400,50), "1p Keyboard Setting");
  SimpleLabel * player2pLabel = new SimpleLabel( Rect<int>(0,0,400,50), "2p Keyboard Setting");
  SimpleLabel * player3pLabel = new SimpleLabel( Rect<int>(0,0,400,50), "3p Keyboard Setting");
  SimpleLabel * player4pLabel = new SimpleLabel( Rect<int>(0,0,400,50), "4p Keyboard Setting");

  // 1p labels
  ToggleLabel *toggleGhost1pLabel = new ToggleLabel(
						    Rect<int>(0,0,400,50), "Ghost",OptionData::playerData1.ghost);
  ToggleLabel *toggleHolder1pLabel = new ToggleLabel(
						     Rect<int>(0,0,400,50),"Holder", OptionData::playerData1.holder);
  NumberLabel *dasDelayTime1pLabel = new NumberLabel(
						     StableData::labelRect, "DAS delay time", "ms", 
						     OptionData::playerData1.dasDelayTime, 0, 1000, 50);
  NumberLabel *horizontalSpeed1pLabel = new NumberLabel(
						      StableData::labelRect, "Horizontal Speed", "G",
						      OptionData::playerData1.horizontalSpeed,0.05, 10, 0.1);
  NumberLabel *normalDropSpeed1pLabel = new NumberLabel(
						      StableData::labelRect, "NormalDrop Speed", "G",
						      OptionData::playerData1.normalDropSpeed,0.05, 20, 0.1);
  NumberLabel *softDropSpeed1pLabel = new NumberLabel(
						      StableData::labelRect, "SoftDrop Speed", "G",
						      OptionData::playerData1.softDropSpeed,0.05, 20, 0.1);
  // 2p labels
  ToggleLabel *toggleGhost2pLabel = new ToggleLabel(
						    Rect<int>(0,0,400,50), "Ghost",OptionData::playerData2.ghost);
  ToggleLabel *toggleHolder2pLabel = new ToggleLabel(
						     Rect<int>(0,0,400,50),"Holder", OptionData::playerData2.holder);
  NumberLabel *dasDelayTime2pLabel = new NumberLabel(
						     StableData::labelRect, "DAS delay time", "ms", 
						     OptionData::playerData2.dasDelayTime, 0, 1000, 50);
  NumberLabel *horizontalSpeed2pLabel = new NumberLabel(
						      StableData::labelRect, "Horizontal Speed", "G",
						      OptionData::playerData2.horizontalSpeed,0.05, 10, 0.1);
  NumberLabel *normalDropSpeed2pLabel = new NumberLabel(
						      StableData::labelRect, "NormalDrop Speed", "G",
						      OptionData::playerData2.normalDropSpeed,0.05, 20, 0.1);
  NumberLabel *softDropSpeed2pLabel = new NumberLabel(
						      StableData::labelRect, "SoftDrop Speed", "G",
						      OptionData::playerData2.softDropSpeed,0.05, 20, 0.1);
  // 3p labels
ToggleLabel *toggleGhost3pLabel = new ToggleLabel(
						    Rect<int>(0,0,400,50), "Ghost",OptionData::playerData3.ghost);
  ToggleLabel *toggleHolder3pLabel = new ToggleLabel(
						     Rect<int>(0,0,400,50),"Holder", OptionData::playerData3.holder);
  NumberLabel *dasDelayTime3pLabel = new NumberLabel(
						     StableData::labelRect, "DAS delay time", "ms", 
						     OptionData::playerData3.dasDelayTime, 0, 1000, 50);
  NumberLabel *horizontalSpeed3pLabel = new NumberLabel(
						      StableData::labelRect, "Horizontal Speed", "G",
						      OptionData::playerData3.horizontalSpeed,0.05, 10, 0.1);
  NumberLabel *normalDropSpeed3pLabel = new NumberLabel(
						      StableData::labelRect, "NormalDrop Speed", "G",
						      OptionData::playerData3.normalDropSpeed,0.05, 20, 0.1);
  NumberLabel *softDropSpeed3pLabel = new NumberLabel(
						      StableData::labelRect, "SoftDrop Speed", "G",
						      OptionData::playerData3.softDropSpeed,0.05, 20, 0.1);
  // 4p labels
ToggleLabel *toggleGhost4pLabel = new ToggleLabel(
						    Rect<int>(0,0,400,50), "Ghost",OptionData::playerData4.ghost);
  ToggleLabel *toggleHolder4pLabel = new ToggleLabel(
						     Rect<int>(0,0,400,50),"Holder", OptionData::playerData4.holder);
  NumberLabel *dasDelayTime4pLabel = new NumberLabel(
						     StableData::labelRect, "DAS delay time", "ms", 
						     OptionData::playerData4.dasDelayTime, 0, 1000, 50);
  NumberLabel *horizontalSpeed4pLabel = new NumberLabel(
						      StableData::labelRect, "Horizontal Speed", "G",
						      OptionData::playerData4.horizontalSpeed,0.05, 10, 0.1);
  NumberLabel *normalDropSpeed4pLabel = new NumberLabel(
						      StableData::labelRect, "NormalDrop Speed", "G",
						      OptionData::playerData4.normalDropSpeed,0.05, 20, 0.1);
  NumberLabel *softDropSpeed4pLabel = new NumberLabel(
						      StableData::labelRect, "SoftDrop Speed", "G",
						      OptionData::playerData4.softDropSpeed,0.05, 20, 0.1);

  /********************************* setters *************************************/
  // 1p setters
  ValueSetter <OptionData::MenuHolderStatus> *key1pSetter= 
    new ValueSetter<OptionData::MenuHolderStatus>(
						  OptionData::menuHolderStatus,
						  OptionData::KEYSETMENU);
  ToggleSetter *toggleGhost1pSetter = 
    new ToggleSetter(OptionData::playerData1.ghost);
  ToggleSetter *toggleHolder1pSetter =
    new ToggleSetter(OptionData::playerData1.holder);
  NumberSetter<Uint32> * dasDelayTime1pSetter = 
    new NumberSetter<Uint32>(OptionData::playerData1.dasDelayTime);
  NumberSetter<double> * horizontalSpeed1pSetter =
    new NumberSetter<double>(OptionData::playerData1.horizontalSpeed);
  NumberSetter<double> * normalDropSpeed1pSetter =
    new NumberSetter<double>(OptionData::playerData1.normalDropSpeed);
  NumberSetter<double> * softDropSpeed1pSetter =
    new NumberSetter<double>(OptionData::playerData1.softDropSpeed);

  // 2p setters
  ValueSetter <OptionData::MenuHolderStatus> *key2pSetter= 
    new ValueSetter<OptionData::MenuHolderStatus>(
						  OptionData::menuHolderStatus,
						  OptionData::KEYSETMENU);
  ToggleSetter *toggleGhost2pSetter = 
    new ToggleSetter(OptionData::playerData2.ghost);
  ToggleSetter *toggleHolder2pSetter =
    new ToggleSetter(OptionData::playerData2.holder);
  NumberSetter<Uint32> * dasDelayTime2pSetter = 
    new NumberSetter<Uint32>(OptionData::playerData2.dasDelayTime);
  NumberSetter<double> * horizontalSpeed2pSetter =
    new NumberSetter<double>(OptionData::playerData2.horizontalSpeed);
  NumberSetter<double> * normalDropSpeed2pSetter =
    new NumberSetter<double>(OptionData::playerData2.normalDropSpeed);
  NumberSetter<double> * softDropSpeed2pSetter =
    new NumberSetter<double>(OptionData::playerData2.softDropSpeed);

  // 3p setters
  ValueSetter <OptionData::MenuHolderStatus> *key3pSetter= 
    new ValueSetter<OptionData::MenuHolderStatus>(
						  OptionData::menuHolderStatus,
						  OptionData::KEYSETMENU);

  ToggleSetter *toggleGhost3pSetter = 
    new ToggleSetter(OptionData::playerData3.ghost);
  ToggleSetter *toggleHolder3pSetter =
    new ToggleSetter(OptionData::playerData3.holder);
  NumberSetter<Uint32> * dasDelayTime3pSetter = 
    new NumberSetter<Uint32>(OptionData::playerData3.dasDelayTime);
  NumberSetter<double> * horizontalSpeed3pSetter =
    new NumberSetter<double>(OptionData::playerData3.horizontalSpeed);
  NumberSetter<double> * normalDropSpeed3pSetter =
    new NumberSetter<double>(OptionData::playerData3.normalDropSpeed);
  NumberSetter<double> * softDropSpeed3pSetter =
    new NumberSetter<double>(OptionData::playerData3.softDropSpeed);

  // 4p setters
  ValueSetter <OptionData::MenuHolderStatus> *key4pSetter= 
    new ValueSetter<OptionData::MenuHolderStatus>(
						  OptionData::menuHolderStatus,
						  OptionData::KEYSETMENU);

  ToggleSetter *toggleGhost4pSetter = 
    new ToggleSetter(OptionData::playerData4.ghost);
  ToggleSetter *toggleHolder4pSetter =
    new ToggleSetter(OptionData::playerData4.holder);
  NumberSetter<Uint32> * dasDelayTime4pSetter = 
    new NumberSetter<Uint32>(OptionData::playerData4.dasDelayTime);
  NumberSetter<double> * horizontalSpeed4pSetter =
    new NumberSetter<double>(OptionData::playerData4.horizontalSpeed);
  NumberSetter<double> * normalDropSpeed4pSetter =
    new NumberSetter<double>(OptionData::playerData4.normalDropSpeed);
  NumberSetter<double> * softDropSpeed4pSetter =
    new NumberSetter<double>(OptionData::playerData4.softDropSpeed);

  /**************************** conbines setters & labels *****************************/
  // 1p combine
  player1pLabel->setAction(key1pSetter);
  toggleGhost1pLabel->setAction(toggleGhost1pSetter);
  toggleHolder1pLabel->setAction(toggleHolder1pSetter);
  dasDelayTime1pLabel->setAction(dasDelayTime1pSetter);
  horizontalSpeed1pLabel->setAction(horizontalSpeed1pSetter);
  normalDropSpeed1pLabel->setAction(normalDropSpeed1pSetter);
  softDropSpeed1pLabel->setAction(softDropSpeed1pSetter);

  // 2p combine
  player2pLabel->setAction(key2pSetter);
  toggleGhost2pLabel->setAction(toggleGhost2pSetter);
  toggleHolder2pLabel->setAction(toggleHolder2pSetter);
  dasDelayTime2pLabel->setAction(dasDelayTime2pSetter);
  horizontalSpeed2pLabel->setAction(horizontalSpeed2pSetter);
  normalDropSpeed2pLabel->setAction(normalDropSpeed2pSetter);
  softDropSpeed2pLabel->setAction(softDropSpeed2pSetter);

  // 3p combine
  player3pLabel->setAction(key3pSetter);
  toggleGhost3pLabel->setAction(toggleGhost3pSetter);
  toggleHolder3pLabel->setAction(toggleHolder3pSetter);
  dasDelayTime3pLabel->setAction(dasDelayTime3pSetter);
  horizontalSpeed3pLabel->setAction(horizontalSpeed3pSetter);
  normalDropSpeed3pLabel->setAction(normalDropSpeed3pSetter);
  softDropSpeed3pLabel->setAction(softDropSpeed3pSetter);

  // 4p combine
  player4pLabel->setAction(key4pSetter);
  toggleGhost4pLabel->setAction(toggleGhost4pSetter);
  toggleHolder4pLabel->setAction(toggleHolder4pSetter);
  dasDelayTime4pLabel->setAction(dasDelayTime4pSetter);
  horizontalSpeed4pLabel->setAction(horizontalSpeed4pSetter);
  normalDropSpeed4pLabel->setAction(normalDropSpeed4pSetter);
  softDropSpeed4pLabel->setAction(softDropSpeed4pSetter);
  
  /************************ construct menus & setup menus ************************/
  // 1p menu
  Menu * player1pMenu = new Menu(StableData::menuRect);
  player1pMenu->addLabel(player1pLabel);
  player1pMenu->addLabel(toggleGhost1pLabel);
  player1pMenu->addLabel(toggleHolder1pLabel);
  player1pMenu->addLabel(dasDelayTime1pLabel);
  player1pMenu->addLabel(horizontalSpeed1pLabel);
  player1pMenu->addLabel(normalDropSpeed1pLabel);
  player1pMenu->addLabel(softDropSpeed1pLabel);

  // 2p menu
  Menu * player2pMenu = new Menu(StableData::menuRect);
  player2pMenu->addLabel(player2pLabel);
  player2pMenu->addLabel(toggleGhost2pLabel);
  player2pMenu->addLabel(toggleHolder2pLabel);
  player2pMenu->addLabel(dasDelayTime2pLabel);
  player2pMenu->addLabel(horizontalSpeed2pLabel);
  player2pMenu->addLabel(normalDropSpeed2pLabel);
  player2pMenu->addLabel(softDropSpeed2pLabel);
  
  // 3p menu
  Menu * player3pMenu = new Menu(StableData::menuRect);
  player3pMenu->addLabel(player3pLabel);
  player3pMenu->addLabel(toggleGhost3pLabel);
  player3pMenu->addLabel(toggleHolder3pLabel);
  player3pMenu->addLabel(dasDelayTime3pLabel);
  player3pMenu->addLabel(horizontalSpeed3pLabel);
  player3pMenu->addLabel(normalDropSpeed3pLabel);
  player3pMenu->addLabel(softDropSpeed3pLabel);

  // 4p menu
  Menu * player4pMenu = new Menu(StableData::menuRect);
  player4pMenu->addLabel(player4pLabel);
  player4pMenu->addLabel(toggleGhost4pLabel);
  player4pMenu->addLabel(toggleHolder4pLabel);
  player4pMenu->addLabel(dasDelayTime4pLabel);
  player4pMenu->addLabel(horizontalSpeed4pLabel);
  player4pMenu->addLabel(normalDropSpeed4pLabel);
  player4pMenu->addLabel(softDropSpeed4pLabel);
  
  /******************************** setup playermenu vector ***********************/
  playerMenuVector.push_back(player1pMenu);
  playerMenuVector.push_back(player2pMenu);
  playerMenuVector.push_back(player3pMenu);
  playerMenuVector.push_back(player4pMenu);
}

void MenuHolder::constructKeySetMenu()
{
  /******************************* labels *************************************/
  // 1p labels
  SimpleLabel * player1pLabel = new SimpleLabel( Rect<int>(0,0,400,50), "1p Keyboard Setting");
  KeySetLabel * moveLeft1pLabel = new KeySetLabel( 
						  StableData::labelRect, "Move Left",
						  OptionData::playerData1.moveLeft);
  KeySetLabel * moveRight1pLabel = new KeySetLabel( 
					   StableData::labelRect, "Move Right",
					   OptionData::playerData1.moveRight);
  KeySetLabel * rotateLeft1pLabel = new KeySetLabel( 
					   StableData::labelRect, "Rotate Left",
					   OptionData::playerData1.rotateLeft);
  KeySetLabel * rotateRight1pLabel = new KeySetLabel( 
					   StableData::labelRect, "Rotate Right",
					   OptionData::playerData1.rotateRight);
  KeySetLabel * softDrop1pLabel = new KeySetLabel( 
					   StableData::labelRect, "Soft Drop",
					   OptionData::playerData1.softDrop);
  KeySetLabel * hardDrop1pLabel = new KeySetLabel( 
					   StableData::labelRect, "Hard Drop",
					   OptionData::playerData1.hardDrop);
  KeySetLabel * hold1pLabel = new KeySetLabel( 
					   StableData::labelRect, "Hold",
					   OptionData::playerData1.hold);
  // 2p labels
  SimpleLabel * player2pLabel = new SimpleLabel( Rect<int>(0,0,400,50), "2p Keyboard Setting");
  KeySetLabel * moveLeft2pLabel = new KeySetLabel( 
						  StableData::labelRect, "Move Left",
						  OptionData::playerData2.moveLeft);
  KeySetLabel * moveRight2pLabel = new KeySetLabel( 
					   StableData::labelRect, "Move Right",
					   OptionData::playerData2.moveRight);
  KeySetLabel * rotateLeft2pLabel = new KeySetLabel( 
					   StableData::labelRect, "Rotate Left",
					   OptionData::playerData2.rotateLeft);
  KeySetLabel * rotateRight2pLabel = new KeySetLabel( 
					   StableData::labelRect, "Rotate Right",
					   OptionData::playerData2.rotateRight);
  KeySetLabel * softDrop2pLabel = new KeySetLabel( 
					   StableData::labelRect, "Soft Drop",
					   OptionData::playerData2.softDrop);
  KeySetLabel * hardDrop2pLabel = new KeySetLabel( 
					   StableData::labelRect, "Hard Drop",
					   OptionData::playerData2.hardDrop);
  KeySetLabel * hold2pLabel = new KeySetLabel( 
					   StableData::labelRect, "Hold",
					   OptionData::playerData2.hold);
  // 3p labels
  SimpleLabel * player3pLabel = new SimpleLabel( Rect<int>(0,0,400,50), "3p Keyboard Setting");
  KeySetLabel * moveLeft3pLabel = new KeySetLabel( 
						  StableData::labelRect, "Move Left",
						  OptionData::playerData3.moveLeft);
  KeySetLabel * moveRight3pLabel = new KeySetLabel( 
					   StableData::labelRect, "Move Right",
					   OptionData::playerData3.moveRight);
  KeySetLabel * rotateLeft3pLabel = new KeySetLabel( 
					   StableData::labelRect, "Rotate Left",
					   OptionData::playerData3.rotateLeft);
  KeySetLabel * rotateRight3pLabel = new KeySetLabel( 
					   StableData::labelRect, "Rotate Right",
					   OptionData::playerData3.rotateRight);
  KeySetLabel * softDrop3pLabel = new KeySetLabel( 
					   StableData::labelRect, "Soft Drop",
					   OptionData::playerData3.softDrop);
  KeySetLabel * hardDrop3pLabel = new KeySetLabel( 
					   StableData::labelRect, "Hard Drop",
					   OptionData::playerData3.hardDrop);
  KeySetLabel * hold3pLabel = new KeySetLabel( 
					   StableData::labelRect, "Hold",
					   OptionData::playerData3.hold);
  // 4p labels
  SimpleLabel * player4pLabel = new SimpleLabel( Rect<int>(0,0,400,50), "4p Keyboard Setting");
  KeySetLabel * moveLeft4pLabel = new KeySetLabel( 
						  StableData::labelRect, "Move Left",
						  OptionData::playerData4.moveLeft);
  KeySetLabel * moveRight4pLabel = new KeySetLabel( 
					   StableData::labelRect, "Move Right",
					   OptionData::playerData4.moveRight);
  KeySetLabel * rotateLeft4pLabel = new KeySetLabel( 
					   StableData::labelRect, "Rotate Left",
					   OptionData::playerData4.rotateLeft);
  KeySetLabel * rotateRight4pLabel = new KeySetLabel( 
					   StableData::labelRect, "Rotate Right",
					   OptionData::playerData4.rotateRight);
  KeySetLabel * softDrop4pLabel = new KeySetLabel( 
					   StableData::labelRect, "Soft Drop",
					   OptionData::playerData4.softDrop);
  KeySetLabel * hardDrop4pLabel = new KeySetLabel( 
					   StableData::labelRect, "Hard Drop",
					   OptionData::playerData4.hardDrop);
  KeySetLabel * hold4pLabel = new KeySetLabel( 
					   StableData::labelRect, "Hold",
					   OptionData::playerData4.hold);
  
  /********************************* setters ********************************/
  // 1p setters
    ValueSetter <OptionData::MenuHolderStatus> *player1pSetter= 
    new ValueSetter<OptionData::MenuHolderStatus>(
						  OptionData::menuHolderStatus,
						  OptionData::PLAYERMENU);
  NumberSetter<SDLKey> *moveLeft1pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData1.moveLeft);
  NumberSetter<SDLKey> *moveRight1pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData1.moveRight);
  NumberSetter<SDLKey> *rotateLeft1pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData1.rotateLeft);
  NumberSetter<SDLKey> *rotateRight1pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData1.rotateRight);
  NumberSetter<SDLKey> *softDrop1pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData1.softDrop);
  NumberSetter<SDLKey> *hardDrop1pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData1.hardDrop);
  NumberSetter<SDLKey> *hold1pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData1.hold);
  
  // 2p setters
  ValueSetter <OptionData::MenuHolderStatus> *player2pSetter= 
    new ValueSetter<OptionData::MenuHolderStatus>(
						  OptionData::menuHolderStatus,
						  OptionData::PLAYERMENU);
  NumberSetter<SDLKey> *moveLeft2pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData2.moveLeft);
  NumberSetter<SDLKey> *moveRight2pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData2.moveRight);
  NumberSetter<SDLKey> *rotateLeft2pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData2.rotateLeft);
  NumberSetter<SDLKey> *rotateRight2pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData2.rotateRight);
  NumberSetter<SDLKey> *softDrop2pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData2.softDrop);
  NumberSetter<SDLKey> *hardDrop2pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData2.hardDrop);
  NumberSetter<SDLKey> *hold2pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData2.hold);

  // 3p setters
  ValueSetter <OptionData::MenuHolderStatus> *player3pSetter= 
    new ValueSetter<OptionData::MenuHolderStatus>(
						  OptionData::menuHolderStatus,
						  OptionData::PLAYERMENU);
  NumberSetter<SDLKey> *moveLeft3pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData3.moveLeft);
  NumberSetter<SDLKey> *moveRight3pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData3.moveRight);
  NumberSetter<SDLKey> *rotateLeft3pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData3.rotateLeft);
  NumberSetter<SDLKey> *rotateRight3pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData3.rotateRight);
  NumberSetter<SDLKey> *softDrop3pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData3.softDrop);
  NumberSetter<SDLKey> *hardDrop3pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData3.hardDrop);
  NumberSetter<SDLKey> *hold3pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData3.hold);
  
  // 4p setters
  ValueSetter <OptionData::MenuHolderStatus> *player4pSetter= 
    new ValueSetter<OptionData::MenuHolderStatus>(
						  OptionData::menuHolderStatus,
						  OptionData::PLAYERMENU);
  NumberSetter<SDLKey> *moveLeft4pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData4.moveLeft);
  NumberSetter<SDLKey> *moveRight4pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData4.moveRight);
  NumberSetter<SDLKey> *rotateLeft4pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData4.rotateLeft);
  NumberSetter<SDLKey> *rotateRight4pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData4.rotateRight);
  NumberSetter<SDLKey> *softDrop4pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData4.softDrop);
  NumberSetter<SDLKey> *hardDrop4pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData4.hardDrop);
  NumberSetter<SDLKey> *hold4pSetter = 
    new NumberSetter<SDLKey>(OptionData::playerData4.hold);
  
  /***************************** combine labels & setters ****************************/
  // 1p combine
  player1pLabel->setAction(player1pSetter);
  moveLeft1pLabel->setAction(moveLeft1pSetter);
  moveRight1pLabel->setAction(moveRight1pSetter);
  rotateLeft1pLabel->setAction(rotateLeft1pSetter);
  rotateRight1pLabel->setAction(rotateRight1pSetter);
  softDrop1pLabel->setAction(softDrop1pSetter);
  hardDrop1pLabel->setAction(hardDrop1pSetter);
  hold1pLabel->setAction(hold1pSetter);

  // 2p combine
  player2pLabel->setAction(player2pSetter);
  moveLeft2pLabel->setAction(moveLeft2pSetter);
  moveRight2pLabel->setAction(moveRight2pSetter);
  rotateLeft2pLabel->setAction(rotateLeft2pSetter);
  rotateRight2pLabel->setAction(rotateRight2pSetter);
  softDrop2pLabel->setAction(softDrop2pSetter);
  hardDrop2pLabel->setAction(hardDrop2pSetter);
  hold2pLabel->setAction(hold2pSetter);

  // 3p combine
  player3pLabel->setAction(player3pSetter);
  moveLeft3pLabel->setAction(moveLeft3pSetter);
  moveRight3pLabel->setAction(moveRight3pSetter);
  rotateLeft3pLabel->setAction(rotateLeft3pSetter);
  rotateRight3pLabel->setAction(rotateRight3pSetter);
  softDrop3pLabel->setAction(softDrop3pSetter);
  hardDrop3pLabel->setAction(hardDrop3pSetter);
  hold3pLabel->setAction(hold3pSetter);

  // 4p combine
  player4pLabel->setAction(player4pSetter);
  moveLeft4pLabel->setAction(moveLeft4pSetter);
  moveRight4pLabel->setAction(moveRight4pSetter);
  rotateLeft4pLabel->setAction(rotateLeft4pSetter);
  rotateRight4pLabel->setAction(rotateRight4pSetter);
  softDrop4pLabel->setAction(softDrop4pSetter);
  hardDrop4pLabel->setAction(hardDrop4pSetter);
  hold4pLabel->setAction(hold4pSetter);

  /************************* construct menus & setup menus ***********************/
  // 1p menu
  Menu * player1pMenu = new Menu(StableData::menuRect);
  player1pMenu->addLabel(player1pLabel);
  player1pMenu->addLabel(moveLeft1pLabel);
  player1pMenu->addLabel(moveRight1pLabel);
  player1pMenu->addLabel(rotateLeft1pLabel);
  player1pMenu->addLabel(rotateRight1pLabel);
  player1pMenu->addLabel(softDrop1pLabel);
  player1pMenu->addLabel(hardDrop1pLabel);
  player1pMenu->addLabel(hold1pLabel);

  // 2p menu
  Menu * player2pMenu = new Menu(StableData::menuRect);
  player2pMenu->addLabel(player2pLabel);
  player2pMenu->addLabel(moveLeft2pLabel);
  player2pMenu->addLabel(moveRight2pLabel);
  player2pMenu->addLabel(rotateLeft2pLabel);
  player2pMenu->addLabel(rotateRight2pLabel);
  player2pMenu->addLabel(softDrop2pLabel);
  player2pMenu->addLabel(hardDrop2pLabel);
  player2pMenu->addLabel(hold2pLabel);

  // 3p menu
  Menu * player3pMenu = new Menu(StableData::menuRect);
  player3pMenu->addLabel(player3pLabel);
  player3pMenu->addLabel(moveLeft3pLabel);
  player3pMenu->addLabel(moveRight3pLabel);
  player3pMenu->addLabel(rotateLeft3pLabel);
  player3pMenu->addLabel(rotateRight3pLabel);
  player3pMenu->addLabel(softDrop3pLabel);
  player3pMenu->addLabel(hardDrop3pLabel);
  player3pMenu->addLabel(hold3pLabel);

  // 4p menu
  Menu * player4pMenu = new Menu(StableData::menuRect);
  player4pMenu->addLabel(player4pLabel);  
  player4pMenu->addLabel(moveLeft4pLabel);
  player4pMenu->addLabel(moveRight4pLabel);
  player4pMenu->addLabel(rotateLeft4pLabel);
  player4pMenu->addLabel(rotateRight4pLabel);
  player4pMenu->addLabel(softDrop4pLabel);
  player4pMenu->addLabel(hardDrop4pLabel);
  player4pMenu->addLabel(hold4pLabel);
  
  /*********************** setup keysetmenu vector ****************************/
  keySetMenuVector.push_back(player1pMenu);
  keySetMenuVector.push_back(player2pMenu);
  keySetMenuVector.push_back(player3pMenu);
  keySetMenuVector.push_back(player4pMenu);
}

void MenuHolder::selectPlayerMenu(const SDL_Event & event)
{
  if( event.type == SDL_KEYDOWN )
    switch( event.key.keysym.sym )
      {
      case SDLK_RIGHT:
	if(playerMenuIter != (playerMenuVector.end() - 1) ){
	  ++playerMenuIter;
	  ++keySetMenuIter;
	}
	break;
      case SDLK_LEFT:
	if( playerMenuIter != playerMenuVector.begin()) {
	  --playerMenuIter;
	  --keySetMenuIter;
	}
	break;
      }
}

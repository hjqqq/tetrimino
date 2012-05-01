#include "valuesetter.h"
#include "menuholder.h"
#include "stabledata.h"
#include "optiondata.h"

MenuHolder::MenuHolder()
{
    constructMainMenu();
    constructStartMenu();
    constructOptionMenu();
}

MenuHolder::~MenuHolder()
{
    delete mainMenu;
    delete startMenu;
    delete optionMenu;
}

void MenuHolder::handleEvent(const SDL_Event &event)
{
    switch (OptionData::menuHolderStatus){
    case OptionData::MAINMENU:
	mainMenu->handleEvent(event);
	break;
    case OptionData::STARTMENU:
	startMenu->handleEvent(event);
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
    case OptionData::STARTMENU:
	startMenu->update();
	break;
    case OptionData::OPTIONMENU:
	optionMenu->update();
	break;
    }
}

void MenuHolder::constructMainMenu()
{
    Label *startLabel = new Label(
	Rect<int>(0, 0, 200, 50),
	new ValueSetter<OptionData::TetriminoStatus>(
	    OptionData::tetriminoStatus,
	    OptionData::GAMELOOP),
	"start");
    Label *optionsLabel = new Label(
	Rect<int>(0, 0, 200, 50),
	new Action(),
	"options");
    Label *quitLabel = new Label(
	Rect<int>(0, 0, 200, 50),
	new ValueSetter<OptionData::TetriminoStatus>(
	    OptionData::tetriminoStatus,
	    OptionData::QUIT),
	"quit");

    mainMenu = new Menu(StableData::menuRect);
    mainMenu->addLabel(startLabel);
    mainMenu->addLabel(optionsLabel);
    mainMenu->addLabel(quitLabel);
}

void MenuHolder::constructStartMenu()
{
    Label *playerOneLabel = new Label(
	Rect<int>(0, 0, 200, 50),
	new Action(),
	"player one : ");
    Label *playerTwoLabel = new Label(
	Rect<int>(0, 0, 200, 50),
	new Action(),
	"player two : ");
    Label *startGameLabel = new Label(
	Rect<int>(0, 0, 200, 50),
	new Action(),
	"start game!!",
	black);

    startMenu = new Menu(StableData::menuRect);
    startMenu->addLabel(playerOneLabel);
    startMenu->addLabel(playerTwoLabel);
    startMenu->addLabel(startGameLabel);    
}

void MenuHolder::constructOptionMenu()
{
    Label *controlLabel = new Label(
	Rect<int>(0, 0, 200, 50),
	new Action(),
	"control");
    Label *soundLabel = new Label(
	Rect<int>(0, 0, 200, 50),
	new Action(),
	"sound");
    Label *creditsLabel = new Label(
	Rect<int>(0, 0, 200, 50),
	new Action(),
	"credits");
    optionMenu = new Menu(StableData::menuRect);
    optionMenu->addLabel(controlLabel);
    optionMenu->addLabel(soundLabel);
    optionMenu->addLabel(creditsLabel);    
}


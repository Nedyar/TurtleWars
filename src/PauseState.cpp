#include "PauseState.h"
#include "Game.h"
#include "MainMenu.h"
#include "Level.h"

PauseState::PauseState()
{
    //ctor
}

PauseState::~PauseState()
{
    //dtor
}

void PauseState::handleEvents()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        action = 2;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        action = 1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        action = 3;
}

void PauseState::update()
{
    if (action == 1)
        menu.MoveUp();
    else if (action == 2)
        menu.MoveDown();
    else if (action == 3)
    {

        switch (menu.GetPressedItem())
        {
        case 0:
            if (clock.getElapsedTime().asMilliseconds()>10)
            resumeGame();
            break;
        case 1:
            loadcontrols();
            break;
        case 2:
            loadMainMenu();
            break;
        }
    }
    action = 0;
}
void PauseState::draw() {
    Level::instance()->draw();
    menu.draw("pause");
}

void PauseState::resumeGame()
{
    Game::instance()->popState();
}

void PauseState::loadMainMenu()
{
    Game::instance()->popState();
    Game::instance()->popState();
    Game::instance()->pushState(new MainMenu());
}

void PauseState::loadcontrols()
{
    //Game::pushState(new ControlsState());
}

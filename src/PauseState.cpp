#include "PauseState.h"
#include "ControlsState.h"
#include "PlayState.h"
#include "MenuState.h"
#include <iostream>

#include "menu.h"


#include <SFML/Graphics.hpp>

#include "GameState.h"


void PauseState::draw(const float dt)
{

    //for shits and giggles let's draw a rectangle to make sure this works.

}

void PauseState::update(const float dt)
{


}

void PauseState::handleInput()
{
    Menu menu("Resume","Controls","Main Menu");

	while (game->window.isOpen())
	{
		sf::Event event;

		while (game->window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
					if(this->clock.getElapsedTime().asSeconds()>1){

                        resumeGame();
                        game->gameLoop();
						std::cout << "Play button has been pressed" << std::endl;


						}
						break;
					case 1:
                        loadcontrols();
                        game->gameLoop();
						std::cout << "Option button has been pressed" << std::endl;
						break;
					case 2:
                        loadMainMenu();
                        game->gameLoop();
						break;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				game->window.close();

				break;

			}
		}

		game->window.clear();

		menu.draw(game->window, "pause");

		game->window.display();

	}

}

PauseState::PauseState(Game* game)
{

    this->game = game;


}

void PauseState::resumeGame()
{
    game->popState();


}

void PauseState::loadMainMenu()
{
    game->popState();
    game->popState();
    game->pushState(new MenuState(this->game));


}

void PauseState::loadcontrols()
{

    game->pushState(new ControlsState(this->game));

}

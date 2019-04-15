#include "SFML/Graphics.hpp"

#include <iostream>

#include "MenuState.h"
#include "ControlsState.h"
#include "GameState.h"
#include "PlayState.h"
#include "menu.h"

MenuState::MenuState(Game* game)
{
    this->game = game;

}

void MenuState::handleInput()
{
/*
    sf::Event event;

    while (game->window.pollEvent(event))
    {
        switch (event.type)
        {
            // Close the window
        case sf::Event::Closed:
            game->window.close();
            break;

            // Change Between game states
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                game->window.close();
            else if (event.key.code == sf::Keyboard::A)
                loadgame();
       break;


        }
    }
    */

    Menu menu("Play","Controls","Exit");

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
                        loadgame();
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
						game->window.close();
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

		menu.draw(game->window, "menu");

		game->window.display();

	}

}


void MenuState::update(const float dt)
{

}


void MenuState::draw(const float dt)
{


}


void MenuState::loadgame()
{

    game->popState();
    game->pushState(new PlayState(this->game,2,3));
  //make this load the play game game state.

}

void MenuState::loadcontrols()
{

    game->pushState(new ControlsState(this->game));

}

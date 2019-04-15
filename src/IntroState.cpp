#include "IntroState.h"

#include "GameState.h"
#include "SplashState.h"
#include "Game.h"
#include <iostream>


#include <SFML/Graphics.hpp>
#define PRUEBA_TIME 6

IntroState::IntroState(Game* game)
{

    this->game = game;

}

void IntroState::draw(const float dt)
{
    game->window.clear();
    //for shits and giggles let's draw a rectangle to make sure this works.
    sf::Texture logo;
    sf::Texture presents;
    sf::Texture tittle;

    logo.loadFromFile("items/logo.png");
    presents.loadFromFile("items/presents.png");
    tittle.loadFromFile("items/turtleroyal.png");

    sf::Sprite spritelogo(logo);
    sf::Sprite spritepresents(presents);
    sf::Sprite spritetittle(tittle);

    spritelogo.setOrigin(0,0);
    spritelogo.setPosition(355,70);

    spritepresents.setOrigin(0,0);
    spritepresents.setPosition(266,380);

    spritetittle.setOrigin(0,0);
    spritetittle.setPosition(130,480);


    game->window.draw(spritelogo);

    if(this->clock.getElapsedTime().asSeconds()>2)
    game->window.draw(spritepresents);

    if(this->clock.getElapsedTime().asSeconds()>4)
    game->window.draw(spritetittle);


}




void IntroState::update(const float dt)
{
    if(this->clock.getElapsedTime().asSeconds()>PRUEBA_TIME)
    loadSplash();

}

void IntroState::handleInput()
{

 sf::Event event;

    while (this->game->window.pollEvent(event))
    {
        switch (event.type)
        {
            /* Close the window */
        case sf::Event::Closed:
            this->game->window.close();
            break;

            //pause game
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                this->game->window.close();

            break;

        }
    }


}



void IntroState::loadSplash()
{
    game->popState();
    game->pushState(new SplashState(this->game));

}

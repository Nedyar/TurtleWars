
#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "SplashState.h"
#include "MenuState.h"
#include "IntroState.h"

#define SPLASH_TIME 20
#define SPLASH_VIDEO_FILEPATH "items/"

SplashState::SplashState(Game* game)
{
    this->game = game;
    sf::Clock clock;
}

void SplashState::draw(const float dt)
{
    game->window.clear();

    sf::Texture tittle;
    tittle.loadFromFile("items/tittle.png");
    sf::Sprite sprite(tittle);

    sprite.setOrigin(635/2,345/2);
    sprite.setPosition(960/2,250);

    sf::Texture load;
    load.loadFromFile("items/load.png");
    sf::Sprite sprites(load);

    sprites.setOrigin(44/2,38/2);



    sf::Texture press;
    press.loadFromFile("items/presskey.png");
    sf::Sprite presskey(press);

    presskey.setOrigin(634/2,41/2);
    presskey.setPosition(960/2,600);

    int x = 234;
    float reloj = 0.5;

    game->window.draw(sprite);
    for(int i = 0 ; i < 8 ; i++){
        if(this->clock.getElapsedTime().asSeconds()>reloj){
            sprites.setPosition(x,500);
            game->window.draw(sprites);
            x+=64;
            reloj += 0.6;
        }
    }
    if(this->clock.getElapsedTime().asSeconds()>5&&(int)this->clock.getElapsedTime().asSeconds()%2==0){
    presskey.setColor(sf::Color::Transparent);

    }
    if(this->clock.getElapsedTime().asSeconds()>5)
    game->window.draw(presskey);

    }



void SplashState::update(const float dt)
{

    if(this->clock.getElapsedTime().asSeconds()>SPLASH_TIME){

    loadMainMenu();
    }


}

void SplashState::handleInput()
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
                loadMainMenu();
            break;

        }
    }


}


void SplashState::loadMainMenu()
{
    game->popState();
    game->pushState(new MenuState(this->game));
  //make this load the play game game state.

}

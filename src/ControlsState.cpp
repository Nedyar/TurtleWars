#include "ControlsState.h"


ControlsState::ControlsState(Game* game)
{

    this->game = game;


}

void ControlsState::draw(const float dt)
{

    sf::Texture controls;
    controls.loadFromFile("items/controls.png");
    sf::Sprite spritecontrols(controls);

    //spritecontrols.setOrigin(0,345);
    spritecontrols.setPosition(0,0);

    game->window.draw(spritecontrols);

}




void ControlsState::update(const float dt)
{


}

void ControlsState::handleInput()
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
         if(this->clock.getElapsedTime().asSeconds()>1)
                returnMenu();
            break;

        }
    }


}



void ControlsState::returnMenu()
{
    game->popState();

}

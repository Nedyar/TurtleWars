#include "SFML/Graphics.hpp"
#include "Game.h"
#include "GameState.h"
#include <iostream>

#define WIDTH 960
#define HEIGHT 640
Game::Game()
{
    window.create(sf::VideoMode(WIDTH, HEIGHT), "TurtleWars");

    window.setFramerateLimit(60);
}

void Game::pushState(GameState* state)
{
    this->states.push(state);
    //this->states.top()->open();
}


void Game::popState()
{
    if (!this->states.empty())
    {
//        this->states.top()->close();//leave state
         this->states.pop();
    }


}



Game::~Game()
{
    while (!states.empty())
        popState();
}


GameState* Game::CurrentState()
{


    if (states.empty()){
        return 0;
        std::cout << "vacio\n";
        }
    else

    {
        //std::cout <<states.top();

        return states.top();
        }
}


void Game::gameLoop()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        //control frame rate (you can ignore this stuff for now)
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        //exception handling
        /*
        if (CurrentState() == PlayState  )
            continue;

            */

        window.setKeyRepeatEnabled(false);


        //get user input for current game state
        CurrentState()->handleInput();

        //update anything neccessary
        CurrentState()->update(dt);

        //clear window
        window.clear((sf::Color(200,200,200,255)));

        //draw anything in the current game state
        CurrentState()->draw(dt);

        window.display();
/*
            for(int i =0;i<states.size();i++){
                if(!states.empty()){
                std::cout <<i<< std::endl;
                }
            }
*/
    }
}

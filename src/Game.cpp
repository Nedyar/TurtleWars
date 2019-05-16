#include "Game.h"

#include <MainMenu.h>

Game* Game::pinstance = nullptr;

Game* Game::instance()
{
    if (pinstance == nullptr)
        pinstance = new Game();
    return pinstance;
}

Game::Game()
{
    pushState(MainMenu::Instance());
    motor = motorSFML::Instance();
}

void Game::pushState(State* state)
{
    states.push(state);
}

void Game::popState()
{
    if (!states.empty())
        states.pop();
}

Game::~Game()
{
    while (!states.empty())
    {
        //delete CurrentState();
        popState();
    }

}

State* Game::CurrentState()
{
    if (!states.empty())
        return states.top();
}

void Game::gameLoop()
{
    // Start the game loop
    while (motor->window.isOpen())
    {
        // Process events
        sf::Event event;
        while (motor->window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
            {
                motor->window.close();
                delete this;
            }

            CurrentState()->handleEvents();
        }

        CurrentState()->update();

        // Clear screen
        motor->clean();
        // Draw the sprite
        CurrentState()->draw(motor->window);
        // Update the window
        motor->display();

    }

}

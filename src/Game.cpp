#include "Game.h"

#include <State.h>
#include <Level.h>

#define WIDTH 960
#define HEIGHT 640

Game* Game::pinstance = nullptr;

Game* Game::instance()
{
    if (pinstance == nullptr)
        pinstance = new Game();
    return pinstance;
}

Game::Game()
{
    pushState(Level::instance(2,3));
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
    while (!states.empty()) {
        //delete CurrentState();
        popState();
    }

}

State* Game::CurrentState()
{
    if (!states.empty())
        return states.top();
}

void Game::handleEvents(sf::RenderWindow &app)
{
    // Process events
    sf::Event event;
    while (app.pollEvent(event))
    {
        // Close window : exit
        if (event.type == sf::Event::Closed)
        {
            app.close();
            delete this;
        }

        CurrentState()->handleEvents();
    }
}

void Game::update()
{
    CurrentState()->update();
}

void Game::draw(sf::RenderWindow &app)
{
    // Clear screen
    app.clear(sf::Color(200,200,200,255));
    // Draw the sprite
    CurrentState()->draw(app);
    // Update the window
    app.display();
}

void Game::gameLoop()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(WIDTH, HEIGHT), "TurtleWars");
    app.setFramerateLimit(60);
    app.setKeyRepeatEnabled(false);

    // Start the game loop
    while (app.isOpen())
    {
        handleEvents(app);
        update();

        draw(app);

    }

}

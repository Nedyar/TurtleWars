#include "Game.h"

#include <IntroState.h>
#include <SplashState.h>

#include <iostream>
using namespace std;

Game* Game::pinstance = nullptr;

Game* Game::instance()
{
    if (pinstance == nullptr)
        pinstance = new Game();
    return pinstance;
}

Game::Game()
{
    resetPoints();

    //pushState(new IntroState());
    pushState(new SplashState());

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

            cout << "Handling events" << endl;
            CurrentState()->handleEvents();
            cout << "Events handled" << endl;
        }

        cout << "Updating" << endl;
        CurrentState()->update();
        cout << "Updated" << endl;

        // Clear screen
        motor->clean();
        // Draw the sprite
        cout << "Drawing" << endl;
        CurrentState()->draw();
        cout << "Drawed" << endl;
        // Update the window
        motor->display();

    }

}

void Game::resetPoints()
{
    for (int i = 0; i < nCharacters; i++)
        points[i] = 0;
}

void Game::addPoint(int player)
{
    if (player >= 0 && player <= nCharacters)
        points[player]++;
}

int* Game::getPoints()
{
    return points;
}


void Game::resetGames()
{
    games = 0;
}

void Game::addGame()
{
    games++;
}

int Game::getGames()
{
    return games;
}

void Game::setNPlayers(int n)
{
    nCharacters = n;
}

int Game::getNPlayers()
{
    return nCharacters;
}

int Game::winner()
{
    int greatestIndex = -1;
    int greatest = 0;
    bool tie = false;

    for (int i = 0; i < nCharacters; i++)
    {
        if (points[i] >= 10) {
            if (greatestIndex == -1 || (greatestIndex != -1 && greatest < points[greatestIndex]))
            {
                greatestIndex = i;
                greatest = points[i];
                tie = false;
            } else if (points[i] == greatest) {
                tie = true;
            }
        }
    }

    if (tie)
        greatestIndex = -1;

    return greatestIndex;

}











/*
// Will deprecate
#include <SFML/Graphics.hpp>

#include <State.h>
#include <Level.h>

#define WIDTH 960
#define HEIGHT 640

State* currentState;

void setState(State* newState)
{
    currentState = newState;
}

void handleEvents(sf::RenderWindow &app)
{
    // Process events
    sf::Event event;
    while (app.pollEvent(event))
    {
        // Close window : exit
        if (event.type == sf::Event::Closed) {
            app.close();
            delete currentState;
        }

        currentState->handleEvents();
    }
}

void update()
{
    currentState->update();
}

void draw(sf::RenderWindow &app)
{
    // Clear screen
    app.clear(sf::Color(200,200,200,255));
    // Draw the sprite
    currentState->draw(app);
    // Update the window
    app.display();
}

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(WIDTH, HEIGHT), "TurtleWars");
    app.setFramerateLimit(60);
    app.setKeyRepeatEnabled(false);

    setState(Level::instance(2,3));

    // Start the game loop
    while (app.isOpen())
    {
        handleEvents(app);
        update();

        draw(app);

    }

    return EXIT_SUCCESS;
}
*/

#include <SFML/Graphics.hpp>

#include <State.h>
#include <Level.h>

#include "Game.h"
#include "MenuState.h"
#include "SplashState.h"
#include "IntroState.h"
#include "PlayState.h"

#define WIDTH 960
#define HEIGHT 640


int main()
{
    Game game; //create game object (so far this constructor just intiializes our window)

    //we will call our menu class "MenuState"

    game.pushState(new  IntroState (&game));  //we want to create a pointer at the game objects address. this will enter our menu.
    //game.pushState(new  PlayState (&game,2,3)); //COMENTAD LO DE ARRIBA Y DESCOMENTAD ESTO PARA IR DIRECTAMENTE AL JUEGO.
    //now loop our game.
    game.gameLoop();

    return 0;
}

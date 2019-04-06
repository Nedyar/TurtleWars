// Will deprecate
#include <SFML/Graphics.hpp>

#include <iostream>
#include <State.h>
#include <Level.h>

#define WIDTH 900
#define HEIGHT 600

State* currentState;

void setState(State* newState) {
    currentState = newState;
}

void handleEvents() {

}

void update() {

}

void render() {

}

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(WIDTH, HEIGHT), "TurtleWars");
    app.setFramerateLimit(60);

    setState(Level::instance(2));

    // Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();

        }

        currentState->handleEvents();
        currentState->update();

        // Clear screen
        app.clear(sf::Color(200,200,200,255));
        // Draw the sprite
        //player->draw(app);
        currentState->draw(app);
        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}

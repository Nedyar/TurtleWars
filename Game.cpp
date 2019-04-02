#include <SFML/Graphics.hpp>
#include <Character.h>
#include <iostream>

#define WIDTH 900
#define HEIGHT 600

int main()
{

    // Create the main window
    sf::RenderWindow app(sf::VideoMode(WIDTH, HEIGHT), "TurtleWars");
    app.setFramerateLimit(60);

    Character *player = new Character(1);

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

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player->walk(true);
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player->walk(false);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            player->jump();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player->crouch();
        else
            player->standUp();



        player->update();


        // Clear screen
        app.clear(sf::Color(200,200,200,255));
        // Draw the sprite
        //player->draw(app);
        player->draw(app);
        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}

void handleEvents() {

}

void update() {

}

void render() {

}

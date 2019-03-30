#include <SFML/Graphics.hpp>

#define UPDATE_TICK_TIME (1000/15) // ~67
#define WIDTH 900
#define HEIGHT 600

int main()
{

    // Create the main window
    sf::RenderWindow app(sf::VideoMode(WIDTH, HEIGHT), "TurtleWars");
    app.setFramerateLimit(60);

    sf::Clock clock;
    sf::Clock updateClock;
    sf::Time timeElapsed;
    double newX = WIDTH/2, lastX = WIDTH/2, posY = 250;
    double velX = 0.001;

// Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
    sprite.setPosition(newX,posY);


    bool firstTime = true;

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

        if (updateClock.getElapsedTime().asMilliseconds() >= UPDATE_TICK_TIME)
        {
            lastX = newX;
            timeElapsed = updateClock.restart();
            newX += velX * (double)timeElapsed.asMicroseconds();

        }

        float percentTick = std::min(1.0, updateClock.getElapsedTime().asMilliseconds()/(double)UPDATE_TICK_TIME);


        int interX = lastX * (1-percentTick) + newX * percentTick;
        if ((interX > WIDTH - sprite.getOrigin().x/2 && velX > 0) || (interX < 0+sprite.getOrigin().x/2) && velX < 0) {
                velX *= -1;
        }

        sprite.setPosition(interX, posY);
// Clear screen
        app.clear();
// Draw the sprite
        app.draw(sprite);
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

#include <SFML/Graphics.hpp>
#include "WeaponSpawner.h"


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


    WeaponSpawner* spawner = new WeaponSpawner(1, 30.0, 30.0);
    Gun* pistola = new Gun(100.0, 30.0);
    ShotGun* escopeta = new ShotGun(170.0, 30.0);
    Grenade* granada = new Grenade(230.0, 30.0);



    bool firstTime = true;

// Start the game loop
    while (app.isOpen())
    {
// Process events
        sf::Event event;
        while (app.pollEvent(event))
        {

            switch(event.type){

                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    app.close();
                    break;

                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:

                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {

                        //Mapeo del cursor
                        case sf::Keyboard::Right:

                        break;

                        case sf::Keyboard::Left:

                        break;

                        case sf::Keyboard::Up:

                        break;

                        case sf::Keyboard::Down:

                        break;

                        case sf::Keyboard::Space: //disparo
                            pistola->shoot();
                        break;

                        case sf::Keyboard::S: //disparo
                            escopeta->shoot();
                        break;

                        case sf::Keyboard::G: //disparo
                            granada->shoot();
                        break;


                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            app.close();
                        break;

                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            std::cout << event.key.code << std::endl;
                        break;

                    }

            }

        }


        if(pistola->shootAnim)
        {
            pistola->shootAnimation();
        }

        if(granada->fire())
        {
            cout << "Boom" << endl; //y destruir la granada
        }


        spawner->spawnWeapon();
        spawner->ballAnimation();


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

        app.draw(spawner->ballSprite1);
        app.draw(spawner->platformSprite);

        app.draw(pistola->gunSprite);
        app.draw(escopeta->shotGunSprite);
        app.draw(granada->grenadeSprite);
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

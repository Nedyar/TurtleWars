#include "Level.h"

Level* Level::pinstance = 0;

Level::Level()
{
    //players = new Character[1]*;
    players = new Character*[1];
    Character* player = new Character(1);
    players[0] = player;
    //players[0] = new Character(0);
}

Level::~Level()
{
    //dtor
}

Level* Level::instance() {
    if (pinstance == 0)
        pinstance = new Level();
    return pinstance;
}

void Level::handleEvents() {
    Character* player = players[0];

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
}

void Level::update() {
    Character* player = players[0];

     player->update();
}

void Level::draw(sf::RenderWindow &app) {
    Character* player = players[0];

     player->draw(app);
}

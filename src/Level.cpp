#include "Level.h"

Level* Level::pinstance = 0;

Level::Level(int nPlayers)
{
    players = new Character*[nPlayers];
    for (int i = 0; i < nPlayers; i++) {
        Character* player = new Character(i+1);
        players[i] = player;
    }
}

Level::~Level()
{
    //dtor
}

Level* Level::instance(int nPlayers) {
    if (pinstance == 0)
        pinstance = new Level(nPlayers);
    return pinstance;
}

void Level::handleEvents() {

    // TODO: Making the event handler control the current number of players
    Character* player = players[0];

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        player->walk(true);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        player->walk(false);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        player->jump();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        player->crouch();
    else
        player->standUp();

    Character* player2 = players[1];

    if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 10)
        player2->walk(true);
    else if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -10)
        player2->walk(false);

    if(sf::Joystick::isButtonPressed(0, 0))
        player2->jump();
    if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 30)
        player2->crouch();
    else
        player2->standUp();

    //std::cout << sf::Joystick::isButtonPressed(0, 0) << std::endl; // A
    //std::cout << sf::Joystick::isButtonPressed(0, 1) << std::endl; // B
    //std::cout << sf::Joystick::isButtonPressed(0, 2) << std::endl; // X
    //std::cout << sf::Joystick::isButtonPressed(0, 3) << std::endl; // Y

}

void Level::update() {
    for (int i = 0; i < sizeof(players)/sizeof(int); i++) {
        Character* player = players[i];
        player->update();
    }
}

void Level::draw(sf::RenderWindow &app) {
    for (int i = 0; i < sizeof(players)/sizeof(int); i++) {
        Character* player = players[i];
        player->draw(app);
    }
}

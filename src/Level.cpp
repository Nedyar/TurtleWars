#include "Level.h"
#include <SFML/Graphics.hpp>

Level* Level::pinstance = 0;

Level::Level(int nPlayers)
{
    players = new Character*[nPlayers];
    for (int i = 0; i < nPlayers; i++) {
        Character* player = new Character(i+1);
        players[i] = player;
    }

    weaponSpawners = new WeaponSpawner*[10];

    for (int i = 0; i < sizeof(weaponSpawners); i++) {
        weaponSpawners[i] = new WeaponSpawner(i%3+1,32*i,200);
    }
}

Level::~Level()
{
    //dtor
}

Level* Level::instance(int nPlayers = 1) {
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

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        player->dropWeapon();
    }
}

void Level::update() {
    for (int i = 0; i < sizeof(players)/sizeof(int); i++) {
        Character* player = players[i];
        player->update();
    }

    for (int i = 0; i < sizeof(weaponSpawners); i++) {
        weaponSpawners[i]->update();
    }

    for (int i = 0; i < weapons.size(); i++) {
        weapons.at(i)->update();
    }
}

void Level::draw(sf::RenderWindow &app) {
    for (int i = 0; i < sizeof(players)/sizeof(int); i++) {
        Character* player = players[i];
        player->draw(app);
    }

    for (int i = 0; i < sizeof(weaponSpawners); i++) {
        weaponSpawners[i]->draw(app);
    }

    for (int i = 0; i < weapons.size(); i++) {
        weapons.at(i)->draw(app);
    }
}

void Level::addWeapon(Weapon* weapon) {
    weapons.push_back(weapon);
}

void Level::addBullet(Bullet* bullet) {
    bullets.push_back(bullet);
}

void Level::removeWeapon(Weapon* weapon) {
    for (int i = 0; i < weapons.size(); i++) {
        if (weapons.at(i) == weapon) {
            weapons.erase(weapons.begin()+i);
            break;
        }
    }
}

void Level::removeBullet(Bullet* bullet) {
    for (int i = 0; i < bullets.size(); i++) {
        if (bullets.at(i) == bullet) {
            bullets.erase(bullets.begin()+i);
            break;
        }
    }
}

#include "Level.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Level* Level::pinstance = 0;

Level::Level(int nPlayers)
{
    players = new Character*[nPlayers];
    for (int i = 0; i < nPlayers; i++) {
        Character* player = new Character(i+1);
        players[i] = player;
    }

    Gun* pistola=new Gun(30.0, 200.0);

    weapons=new Weapon* [1];

    weapons[0]=pistola;

    weaponSpawners = new WeaponSpawner*[10];

    for (int i = 0; i < sizeof(weaponSpawners); i++) {
        weaponSpawners[i] = new WeaponSpawner(i%3+1,32*i,100);
    }

    texture.loadFromFile("img/ground.png");
    sprite = sf::Sprite(texture);
    sprite.setPosition(-25,500);


    //ground = Physics2D::Instance()->createRectangleBody(sprite,8,0);
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

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {

        bulletAux=weapons[0]->shoot();

        if(!bulletAux.empty()){

            for(int i=0; i<bulletAux.size(); i++){

                bullets.push_back(bulletAux.at(i));
            }
        }
        bulletAux.clear();
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

    for (int i = 0; i < sizeof(weapons)/sizeof(Weapon); i++) {
        weapons[i]->update();
    }
}

void Level::draw(sf::RenderWindow &app) {
    for (int i = 0; i < sizeof(players)/sizeof(int); i++) {
        Character* player = players[i];
        player->draw(app);
    }

    for (int i = 0; i < sizeof(weaponSpawners); i++) {
        weaponSpawners[i]->render(app);
    }

    for (int i = 0; i < sizeof(weapons)/sizeof(Weapon); i++) {
        weapons[i]->render(app);
    }

    app.draw(sprite);

    for(int i=0; i<bullets.size(); i++){
        bullets.at(i)->render(app);
    }

}

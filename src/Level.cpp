#include "Level.h"
#include <SFML/Graphics.hpp>

Level* Level::pinstance = 0;

Level::Level(int nPlayers)
{
    nCharacters = nPlayers;
    nWeaponSpawners = 5;

    motorSFML* motor = motorSFML::Instance();
    LevelFactory* factory = LevelFactory::Instance();

    mapa = factory->mapLoader(3);
    players = factory->characterLoader(3, nPlayers);

    weaponSpawners = new WeaponSpawner*[nWeaponSpawners];

    for (int i = 0; i < nWeaponSpawners; i++)
    {
        weaponSpawners[i] = (WeaponSpawner*)malloc(sizeof(WeaponSpawner));
        weaponSpawners[i] = new WeaponSpawner(i%3+1,32*(i+2),384);
    }
}

Level::~Level()
{
    for (int i = 0; i < nCharacters; i++)
    {
        free(players[i]);
    }

    for (int i = 0; i < nWeaponSpawners; i++)
    {
        free(weaponSpawners[i]);
    }
}

Level* Level::instance(int nPlayers = 1)
{
    if (pinstance == 0)
        pinstance = new Level(nPlayers);
    return pinstance;
}

void Level::handleEvents()
{

    // TODO: Making the event handler control the current number of players
    Character* player = players[0];


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        player->startWalking(false);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        player->startWalking(true);
    else
        player->stopWalking();



    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        player->jump();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        player->crouch();
    else
        player->standUp();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        player->dropWeapon();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        player->shoot();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        player->fakeDie();
    }

/*
    if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 10)
        player2->walk(true);
    else if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -10)
        player2->walk(false);

    if(sf::Joystick::isButtonPressed(0, 0))
        player2->jump();
    if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 30)
        player2->crouch();
    else
        player2->standUp();*/

    //std::cout << sf::Joystick::isButtonPressed(0, 0) << std::endl; // A
    //std::cout << sf::Joystick::isButtonPressed(0, 1) << std::endl; // B
    //std::cout << sf::Joystick::isButtonPressed(0, 2) << std::endl; // X
    //std::cout << sf::Joystick::isButtonPressed(0, 3) << std::endl; // Y
}

void Level::update()
{
    for (int i = 0; i < nCharacters; i++)
    {
        Character* player = players[i];
        player->update();
    }

    for (int i = 0; i < nWeaponSpawners; i++)
    {
        weaponSpawners[i]->update();
    }

    for (int i = 0; i < weapons.size(); i++)
    {
        weapons.at(i)->update();
    }

    for(int i=0; i<bullets.size(); i++)
    {
        bullets.at(i)->update();
    }

    Physics2D::Instance()->updateWorld();
}

void Level::draw(sf::RenderWindow &app)
{
    mapa->drawSpriteMatrix(app);

    for (int i = 0; i < nWeaponSpawners; i++)
    {
        weaponSpawners[i]->draw(app);
    }

    for (int i = 0; i < weapons.size(); i++)
    {
        weapons.at(i)->draw(app);
    }

    for (int i = 0; i < bullets.size(); i++)
    {
        bullets.at(i)->draw(app);
    }

    for (int i = 0; i < nCharacters; i++)
    {
        Character* player = players[i];
        player->draw(app);
    }

}

void Level::addWeapon(Weapon* weapon)
{
    weapons.push_back(weapon);
}

void Level::addBullet(Bullet* bullet)
{
    bullets.push_back(bullet);
}

void Level::removeWeapon(Weapon* weapon)
{
    for (int i = 0; i < weapons.size(); i++)
    {
        if (weapons.at(i) == weapon)
        {
            weapons.erase(weapons.begin()+i);
            break;
        }
    }
}

void Level::removeBullet(Bullet* bullet)
{
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets.at(i) == bullet)
        {
            bullets.erase(bullets.begin()+i);
            break;
        }
    }
}

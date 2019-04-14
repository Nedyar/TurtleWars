#include "Level.h"
#include <SFML/Graphics.hpp>

Level* Level::pinstance = 0;

Level::Level(int nPlayers)
{
    nCharacters = nPlayers;
    nWeaponSpawners = 3;

    motorSFML* motor = motorSFML::Instance();
    LevelFactory* factory = LevelFactory::Instance();


    mapa = factory->mapLoader(3);
    players = factory->characterLoader(3, nPlayers);
    weaponSpawners = factory->spawnerLoader(3);
}

Level::~Level()
{
    for (int i = 0; i < nCharacters; i++)
    {
        delete players[i];
    }

    for (int i = 0; i < nWeaponSpawners; i++)
    {
        delete weaponSpawners[i];
    }

    delete mapa;
    delete pinstance;
}

Level* Level::instance(int nPlayers = 1)
{
    if (pinstance == 0) {
        pinstance = new Level(nPlayers);
    }
    return pinstance;
}

void Level::handleEvents()
{

    // TODO: Making the event handler control the current number of players
    Character* player = players[0];
    Character* player2 = players[1];


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
        //cout << "Pulso: E" << endl;
        player->dropWeapon();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        //cout << "Pulso: Space" << endl;
        //player2->jump();
        player->shoot();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        //cout << "Pulso: Q" << endl;
        player->fakeDie();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
    {
        //cout << "Pulso: F" << endl;
        player->takeWeapon();
    }



/*

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        player2->startWalking(true);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        player2->startWalking(false);
    else
        player2->stopWalking();



    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        player2->jump();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        player2->crouch();
    else
        player2->standUp();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        player2->dropWeapon();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        player2->shoot();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        player2->fakeDie();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
    {
        player2->takeWeapon();
    }

    Character* player3 = players[2];


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        player3->startWalking(true);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        player3->startWalking(false);
    else
        player3->stopWalking();



    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        player3->jump();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        player3->crouch();
    else
        player3->standUp();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        player3->dropWeapon();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        player3->shoot();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        player3->fakeDie();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
    {
        player3->takeWeapon();
    }

    Character* player4 = players[3];


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        player4->startWalking(false);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        player4->startWalking(true);
    else
        player4->stopWalking();



    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        player4->jump();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        player4->crouch();
    else
        player4->standUp();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        player4->dropWeapon();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        player4->shoot();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        player4->fakeDie();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
    {
        player4->takeWeapon();
    }

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
    //cout << "Characters:" << endl;
    for (int i = 0; i < nCharacters; i++)
    {
        //cout << players[i] << endl;
        players[i]->update();
    }
    //cout << "WeaponSpawners:" << endl;
    for (int i = 0; i < nWeaponSpawners; i++)
    {
        //cout << "\t"<<weaponSpawners[i] << endl;
        weaponSpawners[i]->update();
    }
    //cout << "Weapons:" << endl;
    for (int i = 0; i < weapons.size(); i++)
    {
        //cout << "\t"<<weapons.at(i) << endl;
        weapons.at(i)->update();
    }
    //cout << "Bullets:" << endl;
    for(int i=0; i<bullets.size(); i++)
    {
        //cout << "\t"<<bullets.at(i) << endl;
        bullets.at(i)->update();
    }
    //cout << "Updateamos world" << endl;
    Physics2D::Instance()->updateWorld();
    //cout << "terminamos update" << endl;
}

void Level::draw(sf::RenderWindow &app)
{
    mapa->drawSpriteMatrix(app);
    mapa->drawBodyMap(app);

    for (int i = 0; i < nWeaponSpawners; i++)
    {
        weaponSpawners[i]->draw(app);
        weaponSpawners[i]->body->pintaRect(app);
    }

    for (int i = 0; i < weapons.size(); i++)
    {
        weapons.at(i)->draw(app);
        weapons.at(i)->body->pintaRect(app);

    }

    for (int i = 0; i < bullets.size(); i++)
    {
        bullets.at(i)->draw(app);
        bullets.at(i)->body->pintaRect(app);
    }

    for (int i = 0; i < nCharacters; i++)
    {
        players[i]->draw(app);
        players[i]->body->pintaRect(app);
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
            cout << "arma borrada" << endl;
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

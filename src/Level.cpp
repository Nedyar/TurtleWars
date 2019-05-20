#include "Level.h"
#include <SFML/Graphics.hpp>
#include <PauseState.h>
#include <Game.h>
#include <ctime>
#include <iostream>
#include <math.h>

#include <ScoreState.h>

#include <iostream>
using namespace std;

Level* Level::pinstance = 0;
bool drawBodies = false;

Level::Level()
{
    motorSFML* motor = motorSFML::Instance();
    LevelFactory* factory = LevelFactory::Instance();
    nCharacters = Game::instance()->getNPlayers();


    srand(time(0));
    int nMap = rand() % 9 + 1;
    mapa = factory->mapLoader(nMap);
    players = factory->characterLoader(nMap, nCharacters);
    weaponSpawners = factory->spawnerLoader(nMap, nWeaponSpawners);

    motor->camara.setCenter(960/2, 640/2);

    texture = new Texture("img/background5.png");
    sprite = new Sprite(*texture->getTexture());
    sprite->setOrigin(sprite->getLocalBounds().width/2,sprite->getLocalBounds().height/2);
    sprite->setPosition(sprite->getLocalBounds().width/2,sprite->getLocalBounds().height/2);
    //background5
}

Level::~Level()
{

    cout << "Destructor of level" << endl;
    for (int i = 0; i < nCharacters; i++)
    {
        delete players[i];
    }
    delete players;

    for (int i = 0; i < nWeaponSpawners; i++)
    {
        delete weaponSpawners[i];
    }
    delete weaponSpawners;

    for (int i = 0; i < weapons.size(); i++)
        delete weapons.at(i);
    weapons.clear();

    for (int i = 0; i < bullets.size(); i++)
        delete bullets.at(i);
    bullets.clear();

    delete mapa;

    delete texture;
    delete sprite;
    //delete pinstance;
}

void Level::Restart()
{
    cout << "Reseting world..." << endl;
    Physics2D::Instance()->resetWorld();
    cout << "World reseted" << endl;
    cout << "Reseting instance..." << endl;
    delete pinstance;
    cout << "Deleted old instance..." << endl;
    pinstance = new Level();
    cout << "Instance reseted" << endl;

}

Level* Level::instance()
{
    if (pinstance == 0)
    {
        pinstance = new Level();
    }
    return pinstance;
}

void Level::handleEvents()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        Game::instance()->pushState(new PauseState());


    Character* player = players[0];

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        player->startWalking(false);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        player->startWalking(true);
    else
        player->stopWalking();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        player->jump();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        player->fakeDie();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        player->lookUp();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        player->crouch();
    else
        player->standUp();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        player->dropWeapon();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        player->shoot();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        player->takeWeapon();

    //START XBOX: 7 OTRO: 9

    /* if(sf::Joystick::isButtonPressed(2, 0))
         cout << "0, 0" << endl;
         if(sf::Joystick::isButtonPressed(2, 1))
         cout << "0, 1" << endl;
         if(sf::Joystick::isButtonPressed(2, 2))
         cout << "0, 2" << endl;
         if(sf::Joystick::isButtonPressed(2, 3))
         cout << "0, 3" << endl;
         if(sf::Joystick::isButtonPressed(2, 4))
         cout << "0, 4" << endl;
         if(sf::Joystick::isButtonPressed(2, 5))
         cout << "0, 5" << endl;
         if(sf::Joystick::isButtonPressed(2, 6))
         cout << "0, 6" << endl;
         if(sf::Joystick::isButtonPressed(2, 7))
         cout << "0, 7" << endl;
         if(sf::Joystick::isButtonPressed(2, 8))
         cout << "0, 8" << endl;
         if(sf::Joystick::isButtonPressed(2, 9))
         cout << "0, 9" << endl;
         if(sf::Joystick::isButtonPressed(2, 10))
         cout << "0, 10" << endl;
         if(sf::Joystick::isButtonPressed(2, 11))
         cout << "0, 11" << endl;
         if(sf::Joystick::isButtonPressed(2, 12))
         cout << "0, 12" << endl;*/

    Character* player2 = players[1];

    if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 15)
            player2->startWalking(false);
        else if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -15)
            player2->startWalking(true);
        else
            player2->stopWalking();

        if(sf::Joystick::isButtonPressed(0, 0))
            player2->jump();
        if(sf::Joystick::isButtonPressed(0, 5))
            player2->fakeDie();
        if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -10)
            player2->lookUp();
        if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 30)
            player2->crouch();
        else
            player2->standUp();

        if(sf::Joystick::isButtonPressed(0, 1))
            player2->dropWeapon();
        if(sf::Joystick::isButtonPressed(0, 2))
            player2->shoot();
        if(sf::Joystick::isButtonPressed(0, 3))
            player2->takeWeapon();


    if (Game::instance()->getNPlayers() > 2)
    {
        Character* player3 = players[2];

        if(sf::Joystick::getAxisPosition(1, sf::Joystick::X) > 15)
            player3->startWalking(false);
        else if(sf::Joystick::getAxisPosition(1, sf::Joystick::X) < -15)
            player3->startWalking(true);
        else
            player3->stopWalking();

        if(sf::Joystick::isButtonPressed(1, 0))
            player3->jump();
        if(sf::Joystick::isButtonPressed(1, 5))
            player3->fakeDie();
        if(sf::Joystick::getAxisPosition(1, sf::Joystick::Y) < -10)
            player3->lookUp();
        if(sf::Joystick::getAxisPosition(1, sf::Joystick::Y) > 30)
            player3->crouch();
        else
            player3->standUp();

        if(sf::Joystick::isButtonPressed(1, 1))
            player3->dropWeapon();
        if(sf::Joystick::isButtonPressed(1, 2))
            player3->shoot();
        if(sf::Joystick::isButtonPressed(1, 3))
            player3->takeWeapon();
    }


    if (Game::instance()->getNPlayers() > 3)
    {
        Character* player4 = players[3];

        if(sf::Joystick::getAxisPosition(2, sf::Joystick::X) > 15)
            player4->startWalking(false);
        else if(sf::Joystick::getAxisPosition(2, sf::Joystick::X) < -15)
            player4->startWalking(true);
        else
            player4->stopWalking();

        if(sf::Joystick::isButtonPressed(2, 0))
            player4->jump();
        if(sf::Joystick::isButtonPressed(2, 5))
            player4->fakeDie();
        if(sf::Joystick::getAxisPosition(2, sf::Joystick::Y) < -10)
            player4->lookUp();
        if(sf::Joystick::getAxisPosition(2, sf::Joystick::Y) > 30)
            player4->crouch();
        else
            player4->standUp();

        if(sf::Joystick::isButtonPressed(2, 1))
            player4->dropWeapon();
        if(sf::Joystick::isButtonPressed(2, 2))
            player4->shoot();
        if(sf::Joystick::isButtonPressed(2, 3))
            player4->takeWeapon();
    }
}

void Level::update()
{
    cout << "Characters:" << endl;
    int alivePlayers = 0;
    int lastPlayer = -1;
    for (int i = 0; i < nCharacters; i++)
    {
        cout << i << endl;
        players[i]->update();
        if (!players[i]->isDead())
        {
            alivePlayers++;
            lastPlayer = i;
        }
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

    if (!mustEnd && alivePlayers <= 1)
    {
        mustEnd = true;
        endClock.restart();
    }

    if (mustEnd && endClock.getElapsedTime().asSeconds() >= 3.7)
    {
        if (lastPlayer != -1){
            players[lastPlayer]->isWinner();
            Game::instance()->addPoint(lastPlayer);
        }
    }

    if (mustEnd && endClock.getElapsedTime().asSeconds() >= 5) {
        Game::instance()->addGame();

        Game::instance()->popState();
        cout << "Stablishing new level..." << endl;
        Restart();
        cout << "New level establised" << endl;
        if (Game::instance()->getGames() < 10)
            Game::instance()->pushState(pinstance);
        else
        {
            Game::instance()->pushState(new ScoreState());
            Game::instance()->resetGames();
        }
        cout << "States de game atualizados" << endl;
    }
}

void Level::draw()
{
    setCamara();
    motorSFML::Instance()->draw(sprite->getSprite());

    mapa->drawSpriteMatrix();
    if (drawBodies)
        mapa->drawBodyMap();

    for (int i = 0; i < nWeaponSpawners; i++)
    {
        weaponSpawners[i]->draw();
        if (drawBodies)
            weaponSpawners[i]->body->pintaRect();
    }

    for (int i = 0; i < weapons.size(); i++)
    {
        weapons.at(i)->draw();
        if (drawBodies)
            weapons.at(i)->body->pintaRect();

    }

    for (int i = 0; i < bullets.size(); i++)
    {
        bullets.at(i)->draw();
        if (drawBodies)
            bullets.at(i)->body->pintaRect();
    }

    for (int i = 0; i < nCharacters; i++)
    {
        players[i]->draw();
        if (drawBodies)
            players[i]->body->pintaRect();
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
            //cout << "arma borrada" << endl;
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

void Level::setCamara()
{
    motorSFML* motor = motorSFML::Instance();
    double xMax = 0, yMax = 0, xCenter = 0, yCenter = 0, width = 0, height = 0;
    double yMin = 1000, xMin = 1000;

    double oldWidth = motor->camara.getSize().x;
    double oldHeight = motor->camara.getSize().y;
    double oldX = motor->camara.getCenter().x;
    double oldY = motor->camara.getCenter().y;



    for (int i = 0; i < nCharacters; i++)
    {
        if(!players[i]->isDead())
        {
            if(players[i]->getBody()->getPositionX() > xMax)
                xMax = players[i]->getBody()->getPositionX();

            if(players[i]->getBody()->getPositionX() < xMin)
                xMin = players[i]->getBody()->getPositionX();

            if(players[i]->getBody()->getPositionY() > yMax)
                yMax = players[i]->getBody()->getPositionY();

            if(players[i]->getBody()->getPositionY() < yMin)
                yMin = players[i]->getBody()->getPositionY();

        }

        /** CALCULO DEL CENTRO DE LA CAMARA **/

        xCenter = (xMax + xMin)/2;
        yCenter = (yMax + yMin)/2;

        xCenter = oldX * 0.8 + xCenter * 0.2;
        yCenter = oldY * 0.8 + yCenter * 0.2;

        /** CALCULO TAMANYO CAMARA **/

        width = xMax - xMin + 300;

        width = oldWidth * 0.95 + width * 0.05;

        if(width < 800)
            width = 800;

        height = width / 1.5;

        if( (yMax - yMin + 200) > height)
        {
            height = (yMax - yMin) + 200;
            width = height * 1.5;
        }

        motor->setCamara(xCenter, yCenter, width, height);
    }
}

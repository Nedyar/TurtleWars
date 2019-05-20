#include "Level.h"
#include <SFML/Graphics.hpp>
#include <PauseState.h>
#include <Game.h>
#include <ctime>
#include <iostream>
#include <math.h>

#include <ScoreState.h>

Level* Level::pinstance = 0;
bool drawBodies = true;

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

    motorSFML::Instance()->setMusic("./sounds/arcade.wav",50);
}

Level::~Level()
{
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

    weapons.clear();
    bullets.clear();

    delete mapa;
    delete pinstance;
}

void Level::Restart() {
    Physics2D::Instance()->resetWorld();
    pinstance = new Level();
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

    // TODO: Making the event handler control the current number of players
    Character* player = players[0];
    Character* player2 = players[1];


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        player->startWalking(false);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        player->startWalking(true);
    else
        player->stopWalking();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        player->jump();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        player->fakeDie();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        player->lookUp();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        player->crouch();
    else
        player->standUp();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        player->dropWeapon();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        player->shoot();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        player->takeWeapon();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        Game::instance()->pushState(new PauseState());


/*
    if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 10)
        player2->startWalking(false);
    else if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -10)
        player2->startWalking(true);
    else
        player2->stopWalking();

    if(sf::Joystick::isButtonPressed(0, 5))
        player2->fakeDie();
    if(sf::Joystick::isButtonPressed(0, 0))
        player2->jump();
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


    /* if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
         player2->startWalking(false);
     else if(sf::Keyboard::isKeyPressed(sf::Keyboard::H))
         player2->startWalking(true);
     else
         player2->stopWalking();



     if(sf::Keyboard::isKeyPressed(sf::Keyboard::U))
         player2->jump();
     if(sf::Keyboard::isKeyPressed(sf::Keyboard::J))
         player2->crouch();
     else
         player2->standUp();

     if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
     {
         player2->dropWeapon();
     }

     if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
     {
         player2->shoot();
     }

     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
     {
         player2->fakeDie();
     }

     if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
     {
         player2->takeWeapon();
     }
     /*
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
         */
    /*

        // Is joystick #0 connected?
    bool connected = sf::Joystick::isConnected(0);
    // How many buttons does joystick #0 support?
    unsigned int buttons = sf::Joystick::getButtonCount(0);
    // Does joystick #0 define a X axis?
    bool hasX = sf::Joystick::hasAxis(0, sf::Joystick::X);
    // Is button #2 pressed on joystick #0?
    bool pressed = sf::Joystick::isButtonPressed(0, 2);
    // What's the current position of the Y axis on joystick #0?
    float position = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

        std::cout << sf::Joystick::isButtonPressed(0, 0) << std::endl; // A
        std::cout << sf::Joystick::isButtonPressed(0, 1) << std::endl; // B
        std::cout << sf::Joystick::isButtonPressed(0, 2) << std::endl; // X
        std::cout << sf::Joystick::isButtonPressed(0, 3) << std::endl; // Y
        std::cout << sf::Joystick::isButtonPressed(0, 4) << std::endl; // L1
        std::cout << sf::Joystick::isButtonPressed(0, 5) << std::endl; // R1
        std::cout << sf::Joystick::isButtonPressed(0, 6) << std::endl; // SELECT
        std::cout << sf::Joystick::isButtonPressed(0, 7) << std::endl; // START
        std::cout << sf::Joystick::isButtonPressed(0, 8) << std::endl; // ANALOG
        std::cout << sf::Joystick::isButtonPressed(0, 9) << std::endl; //
        std::cout << sf::Joystick::isButtonPressed(0, 10) << std::endl; //
        std::cout << sf::Joystick::isButtonPressed(1, 3) << std::endl; //
        std::cout << sf::Joystick::isButtonPressed(1, 0) << std::endl; //
        std::cout << sf::Joystick::isButtonPressed(1, 1) << std::endl; //
        std::cout << sf::Joystick::isButtonPressed(1, 2) << std::endl; //
        std::cout << sf::Joystick::isButtonPressed(1, 3) << std::endl << std::endl; */
}

void Level::update()
{
    //cout << "Characters:" << endl;
    int alivePlayers = 0;
    int lastPlayer = -1;
    for (int i = 0; i < nCharacters; i++)
    {
        //cout << players[i] << endl;
        players[i]->update();
        if (!players[i]->isDead()) {
            alivePlayers++;
            lastPlayer = i;
        }
    }

    if (!mustEnd && alivePlayers <= 1) {
        mustEnd = true;
        endClock.restart();
    }
    if (mustEnd && endClock.getElapsedTime().asSeconds() >= 5) {
        if (lastPlayer != -1)
            Game::instance()->addPoint(lastPlayer);

        Game::instance()->addGame();

        Game::instance()->popState();
        Restart();
        if (Game::instance()->getGames() < 10)
            Game::instance()->pushState(pinstance);
        else {
            Game::instance()->pushState(new ScoreState());
            Game::instance()->resetGames();
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
}

void Level::draw()
{
    setCamara();

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

    motor->setCamara(xCenter, yCenter, width, height);
    }
}

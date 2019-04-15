

#include "PlayState.h"
#include "MenuState.h"
#include <iostream>
#include "Level.h"


#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "PauseState.h"

PlayState* PlayState::pinstance = 0;
bool drawBodies2 = false;

PlayState::PlayState(Game* game, int nPlayers, int nMap)
{

    this->game = game;
    motorSFML* motor = motorSFML::Instance();
    LevelFactory* factory = LevelFactory::Instance();

    nCharacters = nPlayers;

    mapa = factory->mapLoader(nMap);
    players = factory->characterLoader(nMap, nPlayers);
    weaponSpawners = factory->spawnerLoader(nMap, nWeaponSpawners);
}
PlayState::PlayState(int nPlayers, int nMap)
{
    motorSFML* motor = motorSFML::Instance();
    LevelFactory* factory = LevelFactory::Instance();

    nCharacters = nPlayers;

    mapa = factory->mapLoader(nMap);
    players = factory->characterLoader(nMap, nPlayers);
    weaponSpawners = factory->spawnerLoader(nMap, nWeaponSpawners);
}

PlayState* PlayState::instance(int nPlayers, int nMap)
{
    if (pinstance == 0) {
        pinstance = new PlayState(nPlayers, nMap);
    }
    return pinstance;
}

PlayState::~PlayState()
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




void PlayState::draw(const float dt)
{

    mapa->drawSpriteMatrix(game->window);
    if (drawBodies2)
        mapa->drawBodyMap(game->window);

    for (int i = 0; i < nWeaponSpawners; i++)
    {
        weaponSpawners[i]->draw(game->window);
        if (drawBodies2)
            weaponSpawners[i]->body->pintaRect(game->window);
    }

    for (int i = 0; i < weapons.size(); i++)
    {
        weapons.at(i)->draw(game->window);
        if (drawBodies2)
            weapons.at(i)->body->pintaRect(game->window);

    }

    for (int i = 0; i < bullets.size(); i++)
    {
        bullets.at(i)->draw(game->window);
        if (drawBodies2)
            bullets.at(i)->body->pintaRect(game->window);
    }

    for (int i = 0; i < nCharacters; i++)
    {
        players[i]->draw(game->window);
        if (drawBodies2)
            players[i]->body->pintaRect(game->window);
    }

}




void PlayState::update(const float dt)
 //cout << "Characters:" << endl;
 {
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

void PlayState::handleInput()


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

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
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

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
    {
        //cout << "Pulso: F" << endl;
        player->takeWeapon();
    }





    if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
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






    sf::Event event;

    while (this->game->window.pollEvent(event))
    {
        switch (event.type)
        {
            /* Close the window*/
        case sf::Event::Closed:
            this->game->window.close();
            break;

            //pause game
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                PauseGame();
            break;

        }
    }


}



void PlayState::PauseGame()
{

    game->pushState(new PauseState(game));


}
void PlayState::addWeapon(Weapon* weapon)
{
    weapons.push_back(weapon);
}

void PlayState::addBullet(Bullet* bullet)
{
    bullets.push_back(bullet);
}

void PlayState::removeWeapon(Weapon* weapon)
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

void PlayState::removeBullet(Bullet* bullet)
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

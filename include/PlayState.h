#pragma once
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <vector>
#include <State.h>
#include <Character.h>
#include <Bullet.h>
#include <WeaponSpawner.h>
#include <Weapon.h>

#include <Physics2D.h>
#include <Body.h>

#include <motorSFML.h>
#include <LevelFactory.h>
#include <Mapa.h>
#include <Level.h>


#include <SFML/Graphics.hpp>

#include "GameState.h"


class PlayState : public GameState
{

public:



    PlayState(Game* game, int nPlayers, int nMap);

    static PlayState* instance(int nPlayers = 2, int nMap = 3);

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();


    void addWeapon(Weapon* weapon);
    void addBullet(Bullet* bullet);
    void removeWeapon(Weapon* weapon);
    void removeBullet(Bullet* bullet);

        //Will deprecate
    sf::Sprite groundSprite;
    sf::Texture groundTexture;
    Body* groundBody;
PlayState(int nPlayers, int nMap);


protected:


    virtual ~PlayState();

private:
    static PlayState* pinstance;

    Mapa* mapa = nullptr;
    int nCharacters = 0;
    Character **players = nullptr;
    int nWeaponSpawners = 0;
    WeaponSpawner **weaponSpawners = nullptr;
    std::vector<Bullet*> bullets;
    std::vector<Weapon*> weapons;


    void PauseGame();
    sf::Clock clock;


};

#endif // PLAYSTATE_H

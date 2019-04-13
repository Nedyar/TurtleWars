#pragma once

#include <SFML/Graphics.hpp>

class Weapon;

#include <Gun.h>
#include <Grenade.h>
#include <ShotGun.h>

#include <Physics2D.h>
#include <Body.h>
#include <Collidable.h>

class WeaponSpawner : public Collidable
{
public:
    WeaponSpawner(int type, double x, double y);
    virtual ~WeaponSpawner();

    void update();
    void draw(sf::RenderWindow &app);

    bool spawnWeapon();
    Weapon* takeWeapon();

    Body* getBody();

    int getId() override;

private:

    int type;

    Weapon* weaponSpawned;

    Body* body;

    sf::Clock clock;
    sf::Sprite platformSprite;
    sf::Texture platformTexture;
    sf::Sprite ballSprite1;
    sf::Texture ballTexture1;
    sf::Sprite ballSprite2;
};

#include <Weapon.h>

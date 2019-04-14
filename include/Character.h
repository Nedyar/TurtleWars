#pragma once

class Weapon;
class WeaponSpawner;

#include <Gun.h>
#include <SFML/Graphics.hpp>
#include <Physics2D.h>
#include <Box2D.h>
#include <Collidable.h>

const double JUMP_FORCE = 5;
const float xDifArm = 3;
const float yDifArm = 5.5;


class Character : public Collidable
{
public:
    Character(int player, int posx, int posy);
    virtual ~Character();

    int getPlayer();
    Weapon* getWeapon();
    bool shoot();
    bool hasWeapon();

    void stopWalking();
    void startWalking(bool right);
    bool jump();
    bool crouch();
    void standUp();
    void die();
    void fakeDie();

    bool dropWeapon();
    bool takeWeapon();
    void setWeaponSpawnerOver(WeaponSpawner* newWS);
    void setWeaponOver(Weapon* newWeapon);

    void draw(sf::RenderWindow &app);
    void update();

    Body* getBody();

    int getId() override;

protected:

private:
    int player = 0;
    Weapon* weapon = nullptr;
    WeaponSpawner* weaponSpawnerOver = nullptr;
    Weapon* weaponOver = nullptr;

    float xPosture = 0;
    int yPosture = 0;

    bool walking = false;
    bool facingLeft = false;
    bool jumping = false;
    bool onGround = false;
    bool crouching = false;
    bool sliding = false;
    bool dead = false;
    bool fakingDead = false;

    Body* body = nullptr;

    sf::Sprite sprite;
    sf::Texture texture;
    sf::Sprite armSprite;
    sf::Texture armTexture;
};

#include <Weapon.h>
#include <WeaponSpawner.h>

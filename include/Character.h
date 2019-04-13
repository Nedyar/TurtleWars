#pragma once

class Weapon;

#include <Gun.h>
#include <SFML/Graphics.hpp>
#include <Physics2D.h>
#include <Box2D.h>

const double JUMP_FORCE = 5;
const float xDifArm = 3;
const float yDifArm = 5.5;


class Character
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
    bool takeWeapon(Weapon* weapon);

    void draw(sf::RenderWindow &app);
    void update();

    Body* getBody();

protected:

private:
    int player;
    Weapon* weapon;

    float xPosture;
    int yPosture;

    bool walking;
    bool facingLeft;
    bool jumping;
    bool onGround;
    bool crouching;
    bool sliding;
    bool dead;
    bool fakingDead;

    Body* body;

    sf::Sprite sprite;
    sf::Texture texture;
    sf::Sprite armSprite;
    sf::Texture armTexture;
};

#include <Weapon.h>

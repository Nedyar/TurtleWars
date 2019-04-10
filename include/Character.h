#ifndef CHARACTER_H
#define CHARACTER_H

#include <Weapon.h>
#include <Gun.h>
#include <SFML/Graphics.hpp>
#include <Physics2D.h>
#include <Box2D.h>


class Character
{
public:
    Character(int player);
    virtual ~Character();

    int getPlayer();
    Weapon* getWeapon();
    bool shoot();
    bool hasWeapon();

    void walk(bool right);
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

    float posture;

    bool walking;
    bool facingLeft;
    bool jumping;
    bool onGround;
    bool crouching;
    bool sliding;
    bool dead;
    bool fakingDead;

    Body* body;

    double yJumpedFrom;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Sprite armSprite;
    sf::Texture armTexture;
};

#endif // CHARACTER_H

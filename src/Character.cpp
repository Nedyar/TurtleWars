#include "Character.h"

// Will deprecate
#define XINIT 100
#define YINIT 200

Character::Character(int n)
{
    player = n;
    has_weapon = false;
    posture = 0;
    facingLeft = false;
    jumping = false;
    onGround = true;
    dead = false;

    // will deprecate
    texture.loadFromFile("img/quackduck.png");

    sprite = sf::Sprite(texture);

    sf::IntRect rect = sf::IntRect(0,0,32,32);
    sprite.setTextureRect(rect);
    sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
    sprite.setPosition(XINIT*n,YINIT);
}

Character::~Character()
{
    //dtor
}

int Character::getPlayer()
{
    return player;
}

Weapon* Character::getWeapon()
{
    return weapon;
}

bool Character::shoot()
{
    if (has_weapon)
    {
        weapon->shoot();
        return true;
    }
    else
        return false;
}

bool Character::hasWeapon()
{
    return has_weapon;
}

bool Character::dropWeapon() {
    if (has_weapon) {
        has_weapon = false;
        return true;
    }
    return false;
}

bool Character::takeWeapon(Weapon* weapon) {
    if (!has_weapon) {
        this->weapon = weapon;
        has_weapon = true;
        return true;
    }
    return false;
}

void Character::walk(bool right)
{
    if (!dead) {
        this->walking = true;
        if (walking && !sliding)
            this->facingLeft = !right;
    }
}

bool Character::jump()
{
    if (!dead && onGround && !jumping)
    {
        standUp();
        jumping = true;
        yJumpedFrom = sprite.getPosition().y;
        onGround = false;
    }
}

bool Character::crouch()
{
    if (!dead && !crouching && !jumping && onGround)
    {
        crouching = true;
        if (walking)
            sliding = true;

        return true;
    }

    return false;
}

void Character::standUp()
{
    if (!dead) {
        crouching = false;
        sliding = false;
    }
}

void Character::die() {
    dropWeapon();
    dead = true;
}

void Character::draw(sf::RenderWindow &app)
{
    app.draw(sprite);
}

void Character::update()
{
    // TODO: Dead sprite

    // will deprecate
    sf::IntRect rect;
    int ypos = 0;
    if (sliding)
    {
        ypos = 32*2;
        posture = 0;
        if (!facingLeft)
        {
            sprite.setScale(1,1);
            sprite.move(3,0);
        }
        else
        {
            sprite.setScale(-1,1);
            sprite.move(-3,0);
        }
    }
    else if (crouching)
    {
        posture = 5;
        ypos = 32;
    }
    else if (walking)
    {
        posture+=0.2;
        if (posture >= 6)
            posture = 0;

        if (!facingLeft)
        {
            sprite.setScale(1,1);
            sprite.move(3,0);
        }
        else
        {
            sprite.setScale(-1,1);
            sprite.move(-3,0);
        }

    }
    else
        posture = 0;

    rect = sf::IntRect(32*((int)posture),ypos,32,32);


    if (jumping)
    {
        if (yJumpedFrom-75 < sprite.getPosition().y)
        {
            sprite.move(0,-5);
            rect = sf::IntRect(32,32,32,32);
        }
        else
        {
            jumping = false;
            rect = sf::IntRect(32*2,32,32,32);
        }


    }
    else if (!onGround)
    {
        if (sprite.getPosition().y < YINIT)
        {
            sprite.move(0,5);
            rect = sf::IntRect(32*3,32,32,32);
        }

        else
        {
            onGround = true;
            rect = sf::IntRect(32*4,32,32,32);
        }

    }

    walking = false;

    sprite.setTextureRect(rect);
}

sf::Sprite Character::getSprite()
{
    return sprite;
}

#include "Character.h"
#include <Level.h>

// Will deprecate
#define XINIT 480
#define YINIT 100

Character::Character(int n)
{
    player = n;
    weapon = new ShotGun(0,0);
    posture = 0;
    facingLeft = false;
    jumping = false;
    onGround = true;
    dead = false;
    fakingDead = false;

    // will deprecate
    texture.loadFromFile("img/move.png");
    armTexture.loadFromFile("img/arm.png");

    sprite = sf::Sprite(texture);
    armSprite = sf::Sprite(armTexture);

    sf::IntRect rect = sf::IntRect(0,0,32,32);

    sprite.setTextureRect(rect);
    sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
    sprite.setPosition(XINIT*n+3,YINIT);

    armSprite.setTextureRect(rect);
    armSprite.setOrigin(armSprite.getLocalBounds().width/2,armSprite.getLocalBounds().height/2);
    armSprite.setPosition(XINIT*n,YINIT);

    body = Physics2D::Instance()->createRectangleBody(sprite.getPosition().x,sprite.getPosition().y,sprite.getGlobalBounds().width,sprite.getGlobalBounds().height,1);
    body->setFriction(1);
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

Body* Character::getBody()
{
    return body;
}

bool Character::shoot()
{
    if (weapon != nullptr)
    {
        weapon->shoot();
        return true;
    }
    else
        return false;
}

bool Character::hasWeapon()
{
    return weapon != nullptr;
}

bool Character::dropWeapon()
{
    if (weapon != nullptr)
    {
        Level* level = Level::instance(0);
        level->addWeapon(weapon);

        weapon = nullptr;
        return true;
    }
    return false;
}

bool Character::takeWeapon(Weapon* weapon)
{
    if (weapon == nullptr)
    {
        this->weapon = weapon;
        return true;
    }
    return false;
}

void Character::walk(bool right)
{
    if (!dead)
    {
        fakingDead = false;
        walking = true;
        if (walking && !sliding)
            facingLeft = !right;
    }
}

bool Character::jump()
{
    if (!dead && onGround && !jumping)
    {
        posture = 0;
        standUp();
        fakingDead = false;
        jumping = true;
        yJumpedFrom = body->getPositionY();
        onGround = false;
        body->getBody()->SetLinearVelocity((b2Vec2(body->getBody()->GetLinearVelocity().x,10)));
    }
}

bool Character::crouch()
{
    if (!dead && !crouching && !jumping && onGround)
    {
        fakingDead = false;
        crouching = true;
        double vel = body->getBody()->GetLinearVelocity().x;
        if (vel != 0)
        {
            int str = vel*2;

            body->getBody()->ApplyForce(b2Vec2(str,0),body->getBody()->GetPosition(),true);
            sliding = true;
            posture = 1;
        }

        return true;
    }

    return false;
}

void Character::standUp()
{
    if (!dead)
    {
        crouching = false;
        sliding = false;
    }
}

void Character::die()
{
    fakingDead = false;
    dropWeapon();
    dead = true;
}

void Character::fakeDie()
{
    if (!dead)
    {
        dropWeapon();
        fakingDead = true;
    }
}

void Character::draw(sf::RenderWindow &app)
{
    app.draw(sprite);
    if (weapon != nullptr)
        weapon->draw(app);
    app.draw(armSprite);
}

void Character::update()
{
    sf::IntRect rect;
    int yPos;

    if (sliding)
    {
        float str = 1;
        int xDir = 1;
        yPos = 2;

        if (facingLeft)
        {
            xDir *= -1;
            str *= -1;
        }
        sprite.setScale(xDir,1);
        armSprite.setScale(xDir,1);

        posture = 0;
    }
    else if (crouching)
    {
        posture = 1;
        yPos = 2;
    }
    else if (walking)
    {
        float str = 1.5;
        int xDir = 1;
        yPos = 0;
        posture+=0.2;
        if (posture >= 8)
            posture = 0;

        if (facingLeft)
        {
            xDir *= -1;
            str *= -1;
        }
        sprite.setScale(xDir,1);
        armSprite.setScale(xDir,1);
        body->getBody()->SetLinearVelocity(b2Vec2(str,body->getBody()->GetLinearVelocity().y));
    }
    else if (dead || fakingDead)
    {
        yPos = 3;
        posture = 0;
    }
    else
    {
        yPos = 0;
        posture = 0;
    }

    if (jumping)
    {
        yPos = 1;

        if (yJumpedFrom-75 < sprite.getPosition().y)
        {
            if (yJumpedFrom-19 < sprite.getPosition().y)
                posture = 0;
            else if (yJumpedFrom-38 < sprite.getPosition().y)
                posture = 1;
            else if (yJumpedFrom-56 < sprite.getPosition().y)
                posture = 2;
            else
                posture = 3;
        }
        else
        {
            jumping = false;
        }
    }
    else if (!onGround)
    {
        yPos = 1;

        if (sprite.getPosition().y < yJumpedFrom)
        {
            if (sprite.getPosition().y < yJumpedFrom-56)
                posture = 4;
            else if (sprite.getPosition().y < yJumpedFrom-38)
                posture = 5;
            else if (sprite.getPosition().y < yJumpedFrom-19)
                posture = 6;
            else if (sprite.getPosition().y < yJumpedFrom)
                posture = 7;
        }

        else
        {
            onGround = true;
        }
    }

    rect = sf::IntRect(32*((int)posture),yPos*32,32,32);

    sprite.setTextureRect(rect);
    walking = false;

    sprite.setPosition(body->getPositionX(),body->getPositionY());
    armSprite.setPosition(body->getPositionX(),body->getPositionY());

    if (weapon != nullptr)
    {
        if (sliding || crouching)
            weapon->setPos(sprite.getPosition().x,sprite.getPosition().y+3);
        else
            weapon->setPos(sprite.getPosition().x,sprite.getPosition().y);
        weapon->update();
    }
}

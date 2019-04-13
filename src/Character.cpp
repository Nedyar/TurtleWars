#include "Character.h"
#include <Level.h>
#include <typeindex>
#include <iostream>
using namespace std;

Character::Character(int n, int posx, int posy)
{
    player = n;
    takeWeapon(new Grenade(0,0));
    xPosture = 0;
    facingLeft = false;
    jumping = false;
    onGround = false;
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
    sprite.setPosition(posx,posy);

    rect = sf::IntRect(0,0,9,8);
    armSprite.setTextureRect(rect);
    armSprite.setOrigin(armSprite.getLocalBounds().width/2,armSprite.getLocalBounds().height/2);
    armSprite.setPosition(posx,posy);

    body = Physics2D::Instance()->createCharacterBody(sprite.getPosition().x, sprite.getPosition().y);
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
        return weapon->shoot();
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
        weapon->setOwner(nullptr);
        weapon = nullptr;
        free(weapon);
        return true;
    }
    return false;
}

bool Character::takeWeapon(Weapon* weap)
{
    if (weapon == nullptr)
    {
        weap->setOwner(this);
        weapon = (Weapon*)malloc(sizeof(Weapon));
        weapon = weap;
        return true;
    }
    return false;
}

void Character::startWalking(bool left)
{
    if (!dead)
    {
        fakingDead = false;
        walking = true;

        facingLeft = left;
    }
}

void Character::stopWalking()
{
    walking = false;
}

bool Character::jump()
{
    if (!dead && onGround && !jumping)
    {
        body->getBody()->SetLinearVelocity((b2Vec2(body->getBody()->GetLinearVelocity().x,-JUMP_FORCE)));
        xPosture = 0;
        standUp();
        fakingDead = false;
        jumping = true;
        onGround = false;
    }
}

bool Character::crouch()
{
    if (!dead && !crouching)
    {
        fakingDead = false;
        crouching = true;

        double vel = body->getBody()->GetLinearVelocity().x;
        if (vel != 0)
        {
            sliding = true;
            xPosture = 1;
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
    if (!dead && !fakingDead)
        app.draw(armSprite);
}

void Character::update()
{
    cout << "Empezamos a updatear" << endl;
    cout << player << endl;
    cout << weapon << endl;
    cout << xPosture << endl;
    cout << facingLeft << endl;
    cout << jumping  << endl;
    cout << onGround << endl;
    cout << dead << endl;
    cout << fakingDead << endl;
    if (body->getBody()->GetLinearVelocity().y != 0)
        onGround = false;
    else
        onGround = true;

    if (sliding)
    {
        xPosture = 0;
        yPosture = 2;
    }
    else if (crouching)
    {
        xPosture = 1;
        yPosture = 2;

        int xDir = 1;
        if (facingLeft)
        {
            xDir *= -1;
        }
        sprite.setScale(xDir,1);
        armSprite.setScale(xDir,1);
    }
    else if (walking)
    {
        yPosture = 0;
        xPosture += .2;

        if (xPosture >= 8)
        {
            xPosture = 0;
        }

        int xDir = 1;
        float str = 1.5;

        if (facingLeft)
        {
            xDir *= -1;
            str *= -1;
        }
        sprite.setScale(xDir,1);
        armSprite.setScale(xDir,1);

        body->getBody()->SetLinearVelocity(b2Vec2(str,body->getBody()->GetLinearVelocity().y));
    }
    else
    {
        yPosture = 0;
        xPosture = 0;
    }

    if (jumping && !crouching)
    {
        yPosture = 1;

        if (body->getBody()->GetLinearVelocity().y < 0)
        {
            if (body->getBody()->GetLinearVelocity().y < -2.25)
                xPosture = 0;
            else if (body->getBody()->GetLinearVelocity().y < -1.5)
                xPosture = 1;
            else if (body->getBody()->GetLinearVelocity().y < -0.75)
                xPosture = 2;
            else
                xPosture = 3;
        }
        else
        {
            jumping = false;
        }
    }
    else if (!onGround && !crouching)
    {
        yPosture = 1;

        if (body->getBody()->GetLinearVelocity().y > 0)
        {
            if (body->getBody()->GetLinearVelocity().y < 0.75)
                xPosture = 4;
            else if (body->getBody()->GetLinearVelocity().y < 1.5)
                xPosture = 5;
            else if (body->getBody()->GetLinearVelocity().y < 2.25)
                xPosture = 6;
            else
                xPosture = 7;
        }
    }

    if (dead || fakingDead)
    {
        yPosture = 3;
        xPosture = 0;
    }

    int xDir = 1;
    if (facingLeft && !sliding)
    {
        xDir *= -1;
    }

    int armPosY = body->getPositionY()+yDifArm;
    if (crouching)
        armPosY += 3;

    int intX = 0;

    if (weapon != nullptr)
    {
        intX = 9;

        int modx = 0;
        int mody = 0;

        if (typeid(dynamic_cast<Grenade*>(weapon)) == typeid(Gun*))
        {
            modx = 3;
            mody = 4.2;
        }
        else if (typeid(dynamic_cast<Grenade*>(weapon)) == typeid(Grenade*))
        {
            modx = 2.5;
            mody = 4;
        }
        else
        {
            modx = 4;
            mody = 5;
        }

        if (facingLeft && !sliding)
        {
            weapon->setFacingLeft(true);
            modx *= -1;
        }
        else
            weapon->setFacingLeft(false);

        if (crouching)
            weapon->setPos(sprite.getPosition().x+modx,sprite.getPosition().y+3+mody);
        else
            weapon->setPos(sprite.getPosition().x+modx,sprite.getPosition().y+mody);

        weapon->update();

    }

    sf::IntRect bodyRect = sf::IntRect(32*((int)xPosture),yPosture*32,32,32);
    sprite.setTextureRect(bodyRect);
    sprite.setPosition(body->getPositionX(),body->getPositionY());
    //sprite.setRotation(body->getAngle());

    sf::IntRect armRect = sf::IntRect(intX,0,9,8);
    armSprite.setTextureRect(armRect);
    armSprite.setPosition(body->getPositionX()-xDifArm*xDir,armPosY);
    //armSprite.setRotation(body->getAngle());
}

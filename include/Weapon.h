#pragma once

class Character;

#include <SFML/Graphics.hpp>
#include <Bullet.h>
#include <Collidable.h>
#include <Body.h>
#include <Texture.h>
#include <Sprite.h>

class Weapon : public Collidable
{
public:
    virtual bool shoot() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void createBody() = 0;
    void deleteBody();
    void setXVelocity(float velocity);
    void setYVelocity(float velocity);
    void resetClock();

    void setPos(int x, int y);
    void setFacingLeft(bool facing);
    void setOwner(Character* newOwner);
    Character* getOwner();

protected:
    Character* owner = nullptr;
    bool facingLeft = false;

    sf::Clock clock;
    Sprite* sprite;
    Texture* texture;

};

#include <Character.h>

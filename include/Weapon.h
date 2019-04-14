#pragma once

class Character;

#include <SFML/Graphics.hpp>
#include <Bullet.h>
#include <Collidable.h>
#include <Body.h>

using namespace std;

class Weapon : public Collidable
{
public:
    virtual bool shoot() = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &app) = 0;
    virtual void createBody() = 0;
    virtual void deleteBody() = 0;
    virtual void setXVelocity(float velocity) = 0;

    void setPos(int x, int y);
    void setFacingLeft(bool facing);
    void setOwner(Character* newOwner);
    Character* getOwner();

protected:
    Character* owner = nullptr;
    bool facingLeft = false;
    sf::Sprite sprite;
    sf::Texture texture;
    Body* body = nullptr;
};

#include <Character.h>

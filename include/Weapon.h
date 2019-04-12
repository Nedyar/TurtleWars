#ifndef WEAPON_H
#define WEAPON_H

class Character;

#include <SFML/Graphics.hpp>
#include <Bullet.h>

using namespace std;

class Weapon
{
public:
    virtual bool shoot() = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &app) = 0;
    void setPos(int x, int y);
    void setFacingLeft(bool facing);
    void setOwner(Character* newOwner);
    Character* getOwner();

protected:
    Character* owner;
    bool facingLeft;
    sf::Sprite sprite;
    sf::Texture texture;
};

#endif // WEAPON_H

#ifndef WEAPON_H
#define WEAPON_H
#include <SFML/Graphics.hpp>
#include <Bullet.h>
#include <vector>

using namespace std;

class Weapon
{
public:
    virtual bool shoot() = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &app) = 0;
    void setPos(int x, int y);

protected:
    sf::Sprite sprite;
    sf::Texture texture;
};

#endif // WEAPON_H

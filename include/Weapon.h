#ifndef WEAPON_H
#define WEAPON_H
#include <SFML/Graphics.hpp>
#include <Bullet.h>
#include <vector>

using namespace std;

class Weapon
{
    public:
        virtual vector<Bullet*> shoot() = 0;
        virtual void update() = 0;
        virtual void render(sf::RenderWindow &app) = 0;
};

#endif // WEAPON_H

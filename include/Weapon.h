#ifndef WEAPON_H
#define WEAPON_H
#include <SFML/Graphics.hpp>

class Weapon
{
    public:
        virtual bool shoot() = 0;
};

#endif // WEAPON_H

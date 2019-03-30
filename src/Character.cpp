#include "Character.h"

Character::Character(int n)
{
    player = n;
    has_weapon = false;
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

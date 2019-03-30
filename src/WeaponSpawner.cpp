#include "WeaponSpawner.h"

WeaponSpawner::WeaponSpawner()
{
    //ctor
}

WeaponSpawner::~WeaponSpawner()
{
    //dtor
}

bool WeaponSpawner::spawnWeapon(int type)
{
    // if clock and not already a weapown spawned
    switch (type)
    {
    case 1: // Gun
        break;

    case 2: // Grenade
        break;

    case 3: // Shotgun
        break;
    }
    return false;
}

#include "Gun.h"

Gun::Gun()
{
    //ctor
}

Gun::~Gun()
{
    //dtor
}

bool Gun::shoot()
{
    if (ammo > 0)
    {
        ammo--;
        return true;
    }
    else
        return false;
}

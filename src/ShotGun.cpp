#include "ShotGun.h"

ShotGun::ShotGun()
{
    //ctor
}

ShotGun::~ShotGun()
{
    //dtor
}

bool ShotGun::reload()
{
    if (ammo > 0 && shooted)
    {
        shooted = false;
        ammo--;
        return true;
    }
    else
        return false;
}

bool ShotGun::shoot()
{
    if (ammo > 0)
    {
        if (!reload())
        {
            return true;
        }
    }
    return false;
}

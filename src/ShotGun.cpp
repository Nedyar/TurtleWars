#include "ShotGun.h"

ShotGun::ShotGun(double posx, double posy)
{
    shotGunTexture.loadFromFile("img/shotgun.png");
    shotGunSprite.setTexture(shotGunTexture);

    shotGunSprite.setPosition(posx,posy);
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

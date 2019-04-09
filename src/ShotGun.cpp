#include "ShotGun.h"

ShotGun::ShotGun(double posx, double posy)
{
    shotGunTexture.loadFromFile("img/shotgun.png");
    shotGunSprite.setTexture(shotGunTexture);

    ammo=3;
    shooted = false;

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
        cout << "Recarga" << endl;
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
            shooted = true;
            ammo--;
            cout << "Pam" << endl;
            return true;
        }
    }
    else
    {
        cout << "Sin municion" << endl;
        return false;
    }

}

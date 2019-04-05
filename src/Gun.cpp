#include "Gun.h"

Gun::Gun(double posx, double posy)
{
    gunTexture.loadFromFile("img/pistol.png");
    gunSprite.setTexture(gunTexture);



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

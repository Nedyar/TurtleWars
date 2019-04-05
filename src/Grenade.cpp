#include "Grenade.h"

Grenade::Grenade(double posx, double posy)
{
    grenadeTexture.loadFromFile("img/grenade.png");
    grenadeSprite.setTexture(grenadeTexture);

    grenadeSprite.setPosition(posx,posy);
}

Grenade::~Grenade()
{
    //dtor
}

bool Grenade::activate()
{
    if (!activated)
    {
        activated = true;
        return true;
    }
    else
        return false;
}

bool Grenade::fire()
{
    if (activated)
        return true;
    else
        return false;
}

bool Grenade::shoot()
{
    if (!throwed)
    {
        if (!activate())
        {
            fire();
            return true;
        }
    }
    return false;
}

bool Grenade::explode()
{
    return true;
}

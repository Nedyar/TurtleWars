#include "ShotGun.h"

ShotGun::ShotGun(double posx, double posy)
{
    texture.loadFromFile("img/shotgun.png");
    sprite.setTexture(texture);

    ammo=3;
    shooted = false;

    sprite.setPosition(posx,posy);
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
    }
    return false;

}

void ShotGun::update()
{

}

void ShotGun::draw(sf::RenderWindow &app)
{
    app.draw(sprite);
}

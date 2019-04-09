#ifndef SHOTGUN_H
#define SHOTGUN_H

#include <Weapon.h>
#include <iostream>

using namespace std;


class ShotGun : public Weapon
{
    public:
        ShotGun(double posx, double posy);
        virtual ~ShotGun();

        bool shoot() override;
        bool reload();

        sf::Sprite shotGunSprite;
        sf::Texture shotGunTexture;


    protected:

    private:
        int ammo;
        bool shooted;
};

#endif // SHOTGUN_H

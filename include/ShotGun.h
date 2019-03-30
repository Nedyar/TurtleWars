#ifndef SHOTGUN_H
#define SHOTGUN_H

#include <Weapon.h>


class ShotGun : public Weapon
{
    public:
        ShotGun();
        virtual ~ShotGun();

        bool shoot() override;
        bool reload();

    protected:

    private:
        int ammo;
        bool shooted;
};

#endif // SHOTGUN_H

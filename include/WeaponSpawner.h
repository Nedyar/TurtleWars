#ifndef WEAPONSPAWNER_H
#define WEAPONSPAWNER_H

#include <Weapon.h>


class WeaponSpawner
{
    public:
        WeaponSpawner();
        virtual ~WeaponSpawner();

        bool spawnWeapon(int type);

    protected:

    private:
};

#endif // WEAPONSPAWNER_H

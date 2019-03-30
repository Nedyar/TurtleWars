#ifndef GUN_H
#define GUN_H

#include <Weapon.h>


class Gun : public Weapon
{
    public:
        Gun();
        virtual ~Gun();

        bool shoot() override;

    protected:

    private:
        int ammo;
};

#endif // GUN_H

#ifndef GRENADE_H
#define GRENADE_H

#include <Weapon.h>


class Grenade : public Weapon
{
    public:
        Grenade();
        virtual ~Grenade();

        bool shoot() override;
        bool activate();
        bool explode();
        bool fire();

    protected:

    private:
        bool activated;
        bool throwed;
};

#endif // GRENADE_H

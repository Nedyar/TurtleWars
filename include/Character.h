#ifndef CHARACTER_H
#define CHARACTER_H

#include <Weapon.h>


class Character
{
    public:
        Character(int number);
        virtual ~Character();

        int getPlayer();
        Weapon* getWeapon();
        bool shoot();
        bool hasWeapon();


    protected:

    private:
        int player;
        Weapon* weapon;
        bool has_weapon;
};

#endif // CHARACTER_H

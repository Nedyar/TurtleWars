#ifndef GUN_H
#define GUN_H

#include <Weapon.h>


class Gun : public Weapon
{
    public:
        Gun(double posx, double posy);
        virtual ~Gun();

        bool shoot() override;


        sf::Sprite gunSprite;
        sf::Texture gunTexture;




    protected:

    private:
        int ammo;
};

#endif // GUN_H

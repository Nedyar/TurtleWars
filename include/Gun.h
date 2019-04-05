#ifndef GUN_H
#define GUN_H
#include <Weapon.h>
#include <iostream>

using namespace std;


class Gun : public Weapon
{
    public:
        Gun(double posx, double posy);
        virtual ~Gun();

        bool shoot() override;
        void setpos(double posx, double posy);
        void shootAnimation();


        sf::Sprite gunSprite;
        sf::Texture gunTexture;
        sf::Clock clockAnimation;
        bool shootAnim;




    protected:

    private:
        int ammo;
};

#endif // GUN_H

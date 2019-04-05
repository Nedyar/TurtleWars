#ifndef GRENADE_H
#define GRENADE_H

#include <Weapon.h>


class Grenade : public Weapon
{
    public:
        Grenade(double posx, double posy);
        virtual ~Grenade();

        bool shoot() override;
        bool activate();
        bool explode();
        bool fire();

        sf::Sprite grenadeSprite;
        sf::Texture grenadeTexture;

    protected:

    private:
        bool activated;
        bool throwed;
};

#endif // GRENADE_H

#ifndef GRENADE_H
#define GRENADE_H

#include <Weapon.h>
#include <iostream>

using namespace std;


class Grenade : public Weapon
{
    public:
        Grenade(double posx, double posy);
        virtual ~Grenade();

        bool shoot() override;
        bool activate();
        bool explode();
        bool fire();

        void update() override;
        void render(sf::RenderWindow &app) override;


        sf::Sprite grenadeSprite;
        sf::Texture grenadeTexture;
        sf::Clock grenadeTimer;

    protected:

    private:
        double grenadeTime;
        bool activated;
        bool throwed;

};

#endif // GRENADE_H

#ifndef GRENADE_H
#define GRENADE_H

#define GRENADETIME 5

#include <Weapon.h>

class Grenade : public Weapon
{
    public:
        Grenade(double posx, double posy);
        virtual ~Grenade();

        bool shoot() override;
        bool activate();
        bool explode();

        void update() override;
        void draw(sf::RenderWindow &app) override;

        sf::Clock grenadeTimer;

    protected:

    private:
        double grenadeTime;
        bool activated;
};

#endif // GRENADE_H

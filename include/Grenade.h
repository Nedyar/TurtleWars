#ifndef GRENADE_H
#define GRENADE_H

const int GRENADETIME = 5;

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

protected:

private:
    double grenadeTime = 0;
    bool activated = false;

    sf::Clock grenadeTimer;
};

#endif // GRENADE_H

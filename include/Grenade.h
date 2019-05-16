#ifndef GRENADE_H
#define GRENADE_H

const int GRENADETIME = 3;

#include <Weapon.h>

class Grenade : public Weapon
{
public:
    Grenade(double posx, double posy);
    virtual ~Grenade();

    void createBody() override;

    bool shoot() override;
    bool activate();
    bool explode();

    void update() override;
    void draw() override;
    int getId() override;
protected:

private:
    double grenadeTime = 0;
    bool activated = false;
    sf::Clock grenadeClock;
};

#endif // GRENADE_H

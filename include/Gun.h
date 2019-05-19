#ifndef GUN_H
#define GUN_H

#include <Weapon.h>

class Gun : public Weapon
{
public:
    Gun(double posx, double posy);
    virtual ~Gun();

    void update() override;
    void draw() override;

    void createBody() override;

    bool shoot() override;
    void setpos(double posx, double posy);
    void shootAnimation();
    int getId() override;

    void chargeSound();

protected:

private:
    int ammo = 0;
    sf::Clock clockAnimation;
    bool shootAnim = false;

    sf::Sound pistolsound;
    sf::SoundBuffer sbpistol;
};

#endif // GUN_H

#ifndef GUN_H
#define GUN_H

#include <Weapon.h>

class Gun : public Weapon
{
public:
    Gun(double posx, double posy);
    virtual ~Gun();

    void update() override;
    void draw(sf::RenderWindow &app) override;

    bool shoot() override;
    void setpos(double posx, double posy);
    void shootAnimation();

protected:

private:
    int ammo = 0;
    sf::Clock clockAnimation;
    bool shootAnim = false;
};

#endif // GUN_H

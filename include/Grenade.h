#ifndef GRENADE_H
#define GRENADE_H
#include <Texture.h>
#include <Sprite.h>

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
    void explosionAnimation();

    void update() override;
    void draw() override;
    int getId() override;
protected:

private:
    double grenadeTime = 0;
    bool activated = false;
    bool exploded = false;
    sf::Clock grenadeClock;
    sf::Clock animationClock;
    Texture* explosionTexture;
    Sprite* explosionSprite1;
    Sprite* explosionSprite2;
    Sprite* explosionSprite3;
    Sprite* explosionSprite4;
    Sprite* explosionSprite5;
    Sprite* explosionSprite6;
    float randomAnimation1 = 0;
    float randomAnimation2 = 0;
    float randomAnimation3 = 0;
    float randomAnimation4 = 0;
    float randomAnimation5 = 0;
    float randomAnimation6 = 0;

};

#endif // GRENADE_H

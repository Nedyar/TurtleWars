#ifndef SHOTGUN_H
#define SHOTGUN_H

#include <Weapon.h>

class ShotGun : public Weapon
{
public:
    ShotGun(double posx, double posy);
    virtual ~ShotGun();

    bool shoot() override;
    bool reload();

    void update() override;
    void draw(sf::RenderWindow &app) override;

    void shootAnimation();

    sf::Sprite shotGunLoaderSprite;
    sf::Texture shotGunLoaderTexture;
    sf::Clock clockAnimation;
    bool shootAnim;
    bool shootAnimBack;

protected:

private:
    int ammo;
    bool shooted;
};

#endif // SHOTGUN_H

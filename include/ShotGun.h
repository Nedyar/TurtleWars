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

    void createBody() override;

    void shootAnimation();
    int getId() override;
protected:

private:
    int ammo = 0;
    bool shooted = false;

    Sprite* shotGunLoaderSprite;
    Texture* shotGunLoaderTexture;
    sf::Clock clockAnimation;
    bool shootAnim = false;
    bool shootAnimBack = false;
};

#endif // SHOTGUN_H

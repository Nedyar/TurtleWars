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
    void draw() override;

    void createBody() override;

    void shootAnimation();
    int getId() override;

    void chargeSound();

protected:

private:
    int ammo = 0;
    bool shooted = false;

    Sprite* shotGunLoaderSprite;
    Texture* shotGunLoaderTexture;
    sf::Clock clockAnimation;
    bool shootAnim = false;
    bool shootAnimBack = false;

    sf::Sound shotgunsound;
    sf::SoundBuffer sbshotgun;
};

#endif // SHOTGUN_H

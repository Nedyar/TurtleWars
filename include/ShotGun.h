#ifndef SHOTGUN_H
#define SHOTGUN_H

#include <Weapon.h>
#include <iostream>

using namespace std;


class ShotGun : public Weapon
{
    public:
        ShotGun(double posx, double posy);
        virtual ~ShotGun();

        vector<Bullet*> shoot() override;
        bool reload();

        void update() override;
        void render(sf::RenderWindow &app) override;
        void shootAnimation();
        void setpos(double posx, double posy);

        sf::Sprite shotGunSprite;
        sf::Texture shotGunTexture;
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

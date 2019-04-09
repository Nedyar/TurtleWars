#ifndef GUN_H
#define GUN_H
#include <Weapon.h>
#include <iostream>

using namespace std;


class Gun : public Weapon
{
    public:
        Gun(double posx, double posy);
        virtual ~Gun();
        void update() override;
        void render(sf::RenderWindow &app) override;

        std::vector<Bullet*> shoot() override;
        void setpos(double posx, double posy);
        void shootAnimation();

    protected:

    private:
        int ammo;
        sf::Sprite gunSprite;
        sf::Texture gunTexture;
        sf::Clock clockAnimation;
        bool shootAnim;
};

#endif // GUN_H

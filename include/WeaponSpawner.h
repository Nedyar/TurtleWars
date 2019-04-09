#ifndef WEAPONSPAWNER_H
#define WEAPONSPAWNER_H
#include <SFML/Graphics.hpp>

#include <Weapon.h>
#include <Gun.h>
#include <Grenade.h>
#include <ShotGun.h>

class WeaponSpawner
{
    public:
        WeaponSpawner(int type, double x, double y);
        virtual ~WeaponSpawner();

        void setpos();
        void update();
        void draw(sf::RenderWindow &app);

        bool spawnWeapon();
        void ballAnimation();

    protected:

    private:

        int type;

        bool created;
        bool animationAux;
        bool animationScale;

        double posx;
        double posy;

        Weapon* weaponSpawned;

        sf::Clock clock;
        sf::Clock clockA;
        sf::Sprite platformSprite;
        sf::Texture platformTexture;
        sf::Sprite ballSprite1;
        sf::Texture ballTexture1;
        sf::Sprite ballSprite2;


};

#endif // WEAPONSPAWNER_H

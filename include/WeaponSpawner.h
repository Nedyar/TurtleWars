#ifndef WEAPONSPAWNER_H
#define WEAPONSPAWNER_H
#include <SFML/Graphics.hpp>

#include <Weapon.h>
#include <Gun.h>
#include <Grenade.h>
#include <ShotGun.h>
#include <iostream>

using namespace std;


class WeaponSpawner
{
    public:
        WeaponSpawner(int type, double x, double y);
        virtual ~WeaponSpawner();
        void setpos();

        bool spawnWeapon();
        void ballAnimation();



        bool created;
        bool animationAux;
        bool animationScale;
        double posx;
        double posy;
        sf::Clock clock;
        sf::Clock clockA;
        sf::Sprite platformSprite;
        sf::Texture platformTexture;
        sf::Sprite ballSprite1;
        sf::Texture ballTexture1;
        sf::Sprite ballSprite2;


    protected:

    private:
        int type;


};

#endif // WEAPONSPAWNER_H

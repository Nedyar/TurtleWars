#ifndef LEVEL_H
#define LEVEL_H

#include <State.h>
#include <Character.h>
#include <Bullet.h>
#include <WeaponSpawner.h>
#include <Weapon.h>
#include <Physics2D.h>
#include <vector>

using namespace std;


class Level : public State
{
    public:
        static Level* instance(int nPlayers);

        void handleEvents() override;
        void update() override;
        void draw(sf::RenderWindow &app) override;
    protected:
        Level(int nPlayers);
        virtual ~Level();

    private:
        static Level* pinstance;

        Character **players;
        vector<Bullet*> bullets;
        vector<Bullet*> bulletAux;
        WeaponSpawner **weaponSpawners;
        Weapon **weapons;

        Body *ground;

        // Will deprecate
        sf::Texture texture;
        sf::Sprite sprite;

};

#endif // LEVEL_H

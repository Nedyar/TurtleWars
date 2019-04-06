#ifndef LEVEL_H
#define LEVEL_H

#include <State.h>
#include <Character.h>
#include <Bullet.h>
#include <WeaponSpawner.h>
#include <Weapon.h>


class Level : public State
{
    public:
        static Level* instance(int nPlayers);

        void handleEvents() override;
        void update() override;
        void draw(sf::RenderWindow &app) override;

        Character **players;
        Bullet **bullets;
        WeaponSpawner **weaponSpawners;
        Weapon **weapons;

    protected:
        Level(int nPlayers);
        virtual ~Level();

    private:
        static Level* pinstance;
};

#endif // LEVEL_H

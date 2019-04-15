#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <State.h>
#include <Character.h>
#include <Bullet.h>
#include <WeaponSpawner.h>
#include <Weapon.h>

#include <Physics2D.h>
#include <Body.h>

#include <motorSFML.h>
#include <LevelFactory.h>
#include <Mapa.h>


class Level : public State
{
public:
    static Level* instance(int nPlayers = 2, int nMap = 3);

    void handleEvents() override;
    void update() override;
    void draw(sf::RenderWindow &app) override;

    void addWeapon(Weapon* weapon);
    void addBullet(Bullet* bullet);
    void removeWeapon(Weapon* weapon);
    void removeBullet(Bullet* bullet);

protected:
    Level(int nPlayers, int nMap);
    virtual ~Level();

private:
    static Level* pinstance;

    Mapa* mapa = nullptr;
    int nCharacters = 0;
    Character **players = nullptr;
    int nWeaponSpawners = 0;
    WeaponSpawner **weaponSpawners = nullptr;
    std::vector<Bullet*> bullets;
    std::vector<Weapon*> weapons;

};

#endif // LEVEL_H

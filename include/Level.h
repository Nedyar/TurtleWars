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

#include "GameState.h"


class Level : public GameState
{
public:
Level(Game* game);

    static Level* instance(int nPlayers = 2, int nMap = 3);

     void draw(const float dt);
     void update(const float dt);
     void handleInput();

    void addWeapon(Weapon* weapon);
    void addBullet(Bullet* bullet);
    void removeWeapon(Weapon* weapon);
    void removeBullet(Bullet* bullet);

    //Will deprecate
    sf::Sprite groundSprite;
    sf::Texture groundTexture;
    Body* groundBody;

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

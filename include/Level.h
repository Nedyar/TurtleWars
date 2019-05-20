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
    static Level* instance();
    void Restart();

    void handleEvents() override;
    void update() override;
    void draw() override;

    void addWeapon(Weapon* weapon);
    void addBullet(Bullet* bullet);
    void removeWeapon(Weapon* weapon);
    void removeBullet(Bullet* bullet);
    void setCamara();

protected:
    Level();
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

    Texture* texture;
    Sprite* sprite;

    bool mustEnd = false;
    sf::Clock endClock;

};

#endif // LEVEL_H

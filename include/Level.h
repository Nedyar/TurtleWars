#ifndef LEVEL_H
#define LEVEL_H

#include <State.h>
#include <Character.h>
#include <Bullet.h>
#include <WeaponSpawner.h>
#include <Weapon.h>
#include <vector>
#include <Physics2D.h>
#include <Body.h>
#include <motorSFML.h>
#include <LevelFactory.h>
#include <Mapa.h>


class Level : public State
{
public:
    static Level* instance(int nPlayers);

    void handleEvents() override;
    void update() override;
    void draw(sf::RenderWindow &app) override;

    void addWeapon(Weapon* weapon);
    void addBullet(Bullet* bullet);
    void removeWeapon(Weapon* weapon);
    void removeBullet(Bullet* bullet);

    //Will deprecate
    sf::Sprite groundSprite;
    sf::Texture groundTexture;
    Body* groundBody;

protected:
    Level(int nPlayers = 1);
    virtual ~Level();

private:
    static Level* pinstance;

    Mapa* mapa;
    Character **players;
    WeaponSpawner **weaponSpawners;
    std::vector<Bullet*> bullets;
    std::vector<Weapon*> weapons;

};

#endif // LEVEL_H

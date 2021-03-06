#pragma once

class Weapon;
class WeaponSpawner;

#include <Gun.h>
#include <SFML/Graphics.hpp>
#include <Physics2D.h>
#include <Box2D.h>
#include <Collidable.h>
#include <vector>

const double JUMP_FORCE = 5;
const float xDifArm = 3;
const float yDifArm = 5.5;

const int LINE_OF_DEATH=750;


class Character : public Collidable
{
public:
    Character(int player, int posx, int posy);
    virtual ~Character();

    int getPlayer();
    Weapon* getWeapon();
    bool shoot();
    bool hasWeapon();

    void stopWalking();
    void startWalking(bool right);
    bool jump();
    bool crouch();
    void standUp();
    void die();
    void kill();
    void fakeDie();
    void lookUp();

    bool dropWeapon();
    bool takeWeapon();
    void swapWeapon();
    void setWeaponSpawnerOver(WeaponSpawner* newWS);
    void addWeaponOver(Weapon* newWeapon);
    void removeWeaponOver(Weapon* newWeapon);

    void isWinner();

    void musicCharger();

    void draw();
    void update();

    Body* getBody();
    bool isDead();
    int getId() override;

protected:

private:
    int player = 0;
    Weapon* weapon = nullptr;
    WeaponSpawner* weaponSpawnerOver = nullptr;
    std::vector<Weapon*> weaponsOver;

    float xPosture = 0;
    int yPosture = 0;

    float width = 0.f;
    float height = 0.f;
    bool bigBody = true;

    bool walking = false;
    bool facingLeft = false;
    bool mustFace = false;
    bool jumping = false;
    bool onGround = false;
    bool crouching = false;
    bool sliding = false;
    bool dead = false;
    bool mustDie = false;
    bool fakingDead = false;
    bool lookingUp = false;

    bool deathplayed=false;
    bool crouchplayed=false;

    double xPositionLastOld = 0;
    double xPositionOld = 0;
    double xPositionLast = 0;
    double xPositionNew = 0;

    bool cancelForces = false;
    bool first = true;
    bool lastOldFacingLeft = false;
    bool oldFacingLeft = false;
    bool lastFacingLeft = false;
    bool winner = false;

    //Body* body = nullptr;

    Sprite* sprite;
    Texture* texture;
    Sprite* armSprite;
    Texture* armTexture;


    sf::Sound jumpsound;
    sf::SoundBuffer sbjump;
    sf::Sound deathsound;
    sf::SoundBuffer sbdeath;
    sf::Sound crouchsound;
    sf::SoundBuffer sbcrouch;
    sf::Sound pickupsound;
    sf::SoundBuffer sbpickup;

    sf::Font font;
    sf::Text textWinner;

};

#include <Weapon.h>
#include <WeaponSpawner.h>

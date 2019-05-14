#include "Character.h"
#include <Level.h>
#include <typeindex>
#include <motorSFML.h>

Character::Character(int n, int posx, int posy)
{
    id = 1;
    player = n;
    xPosture = 0;
    yPosture = 0;
    weapon = nullptr;
    weaponSpawnerOver = nullptr;
    walking = false;
    facingLeft = false;
    jumping = false;
    onGround = false;
    crouching = false;
    sliding = false;
    dead = false;
    fakingDead = false;
    mustDie = false;
    lookingUp = false;

    // will deprecate
    switch (player)
    {
    case 1:
        texture = new Texture("img/move.png"); //texture.loadFromFile("img/move.png");
        break;
    case 2:
        texture = new Texture("img/move_red.png");
        break;
    case 3:
        texture = new Texture("img/move_blue.png");
        break;
    default:
        texture = new Texture("img/move_yellow.png");
        break;
    }
    armTexture = new Texture("img/arm.png");

    sprite = new Sprite(*texture->getTexture());
    armSprite = new Sprite(*armTexture->getTexture());

    //sf::IntRect rect = sf::IntRect(0,0,32,32);
    sprite->setTextureRect(0,0,32,32);
    sprite->setOrigin(sprite->getLocalBounds().width/2,sprite->getLocalBounds().height/2);
    sprite->setPosition(posx,posy);

    //rect = sf::IntRect(0,0,9,8);
    armSprite->setTextureRect(0,0,9,8);
    armSprite->setOrigin(armSprite->getLocalBounds().width/2,armSprite->getLocalBounds().height/2);
    armSprite->setPosition(posx,posy);
    float width = sprite->getLocalBounds().width;
    float height = sprite->getLocalBounds().height;
    body = Physics2D::Instance()->createCharacterBody(posx,posy,width,height);
    body->setUserData(this);
}

Character::~Character()
{
    //dtor
}

int Character::getPlayer()
{
    return player;
}

Weapon* Character::getWeapon()
{
    return weapon;
}

Body* Character::getBody()
{
    return body;
}

bool Character::shoot()
{
    if (weapon != nullptr)
    {
        return weapon->shoot();
    }
    else
        return false;
}

bool Character::hasWeapon()
{
    return weapon != nullptr;
}

void Character::swapWeapon()
{
    if (weapon == nullptr)
        takeWeapon();
    else
        dropWeapon();
}

bool Character::dropWeapon()
{
    if (weapon != nullptr)
    {
        Level* level = Level::instance(0);
        level->addWeapon(weapon);


        weapon->resetClock();
        weapon->setOwner(nullptr);
        weapon->createBody();

        if (lookingUp)
            weapon->setYVelocity(-JUMP_FORCE);
        else
        {
            int xDir = 1 - facingLeft*2;
            weapon->setXVelocity(body->getBody()->GetLinearVelocity().x+4*xDir);
        }

        weapon = nullptr;

        //delete weapon;
        return true;
    }
    return false;
}

bool Character::takeWeapon()
{

    if (weapon == nullptr)
    {

        Weapon* newWeapon = nullptr;

        if (!weaponsOver.empty())
        {
            //cout << "estoy sobre arma" << endl;
            Weapon* weaponOver = weaponsOver.front();
            weaponsOver.erase(weaponsOver.begin());

            Level::instance(0)->removeWeapon(weaponOver);
            newWeapon = weaponOver;
            weaponOver = nullptr;
        }
        else if (weaponSpawnerOver != nullptr)
        {

            newWeapon = weaponSpawnerOver->takeWeapon();
        }

        if (newWeapon != nullptr)
        {
            newWeapon->setOwner(this);
            weapon = newWeapon;
            weapon->deleteBody();
            //cout << "Arma equipada" << endl;
            return true;
        }
    }

    //cout << "Arma no equipada" << endl;;

    return false;
}

void Character::setWeaponSpawnerOver(WeaponSpawner* newWS)
{
    weaponSpawnerOver = newWS;
}

void Character::addWeaponOver(Weapon* newWeapon)
{
    weaponsOver.push_back(newWeapon);
}

void Character::removeWeaponOver(Weapon* newWeapon)
{
    for (int i = 0; i < weaponsOver.size(); i++)
    {
        if (weaponsOver.at(i) == newWeapon)
        {
            weaponsOver.erase(weaponsOver.begin()+i);
            break;
        }
    }
}

void Character::lookUp()
{
    lookingUp = true;
}

void Character::startWalking(bool left)
{
    if (!dead)
    {
        fakingDead = false;
        walking = true;

        if (!sliding)
            facingLeft = left;
    }
}

void Character::stopWalking()
{
    walking = false;
}

bool Character::jump()
{
    if (!dead && onGround && !jumping)
    {
        body->getBody()->SetLinearVelocity((b2Vec2(body->getBody()->GetLinearVelocity().x,-JUMP_FORCE)));
        xPosture = 0;
        standUp();
        fakingDead = false;
        jumping = true;
        onGround = false;
    }
}

bool Character::crouch()
{
    if (!dead && !crouching)
    {
        fakingDead = false;
        crouching = true;

        double vel = body->getBody()->GetLinearVelocity().x;
        if (vel != 0)
        {
            sliding = true;
            xPosture = 1;
        }

        return true;
    }

    return false;
}

void Character::standUp()
{
    if (!dead)
    {
        crouching = false;
        sliding = false;
    }
}

void Character::kill()
{
    mustDie = true;
}

void Character::die()
{
    stopWalking();
    fakingDead = false;
    dropWeapon();
    dead = true;
}

void Character::fakeDie()
{
    if (!dead)
    {
        stopWalking();
        dropWeapon();
        fakingDead = true;
    }
}

void Character::draw(sf::RenderWindow &app)
{
    motorSFML *motor = motorSFML::Instance();
    //app.draw(sprite);
    motor->draw(sprite->getSprite());
    if (weapon != nullptr)
        weapon->draw(app);
    if (!dead && !fakingDead)
        motor->draw(armSprite->getSprite()); //app.draw(armSprite);
}

void Character::update()
{
    if (mustDie)
        die();

    if (body->getBody()->GetLinearVelocity().y != 0)
        onGround = false;
    else
        onGround = true;

    if (sliding)
    {
        xPosture = 0;
        yPosture = 2;
    }
    else if (crouching)
    {
        xPosture = 1;
        yPosture = 2;

        int xDir = 1 - facingLeft*2;
        sprite->setScale(xDir,1);
        armSprite->setScale(xDir,1);
    }
    else if (walking)
    {
        yPosture = 0;
        xPosture += .2;

        if (xPosture >= 8)
        {
            xPosture = 0;
        }

        int xDir = 1 - facingLeft*2;
        float str = 1.5 - facingLeft*3;

        sprite->setScale(xDir,1);
        armSprite->setScale(xDir,1);

        body->getBody()->SetLinearVelocity(b2Vec2(str,body->getBody()->GetLinearVelocity().y));
    }
    else
    {
        yPosture = 0;
        xPosture = 0;
    }

    if (jumping && !crouching)
    {
        yPosture = 1;

        if (body->getBody()->GetLinearVelocity().y < 0)
        {
            if (body->getBody()->GetLinearVelocity().y < -2.25)
                xPosture = 0;
            else if (body->getBody()->GetLinearVelocity().y < -1.5)
                xPosture = 1;
            else if (body->getBody()->GetLinearVelocity().y < -0.75)
                xPosture = 2;
            else
                xPosture = 3;
        }
        else
        {
            jumping = false;
        }
    }
    else if (!onGround && !crouching)
    {
        yPosture = 1;

        if (body->getBody()->GetLinearVelocity().y > 0)
        {
            if (body->getBody()->GetLinearVelocity().y < 0.75)
                xPosture = 4;
            else if (body->getBody()->GetLinearVelocity().y < 1.5)
                xPosture = 5;
            else if (body->getBody()->GetLinearVelocity().y < 2.25)
                xPosture = 6;
            else
                xPosture = 7;
        }
    }

    if (dead || fakingDead)
    {
        yPosture = 3;
        xPosture = 0;
    }

    int armPosY = body->getPositionY()+yDifArm;
    if (crouching)
        armPosY += 3;

    int intX = 0;
    if (weapon != nullptr)
    {
        intX = 9;

        int modx = 0;
        int mody = 0;

        if (typeid(dynamic_cast<Grenade*>(weapon)) == typeid(Gun*))
        {
            modx = 3;
            mody = 4.2;
        }
        else if (typeid(dynamic_cast<Grenade*>(weapon)) == typeid(Grenade*))
        {
            modx = 2.5;
            mody = 4;
        }
        else
        {
            modx = 4;
            mody = 5;
        }


        if (facingLeft)
        {
            weapon->setFacingLeft(true);
            modx *= -1;
        }
        else
            weapon->setFacingLeft(false);

        if (crouching)
            weapon->setPos(sprite->getPosition().x+modx,sprite->getPosition().y+3+mody);
        else
            weapon->setPos(sprite->getPosition().x+modx,sprite->getPosition().y+mody);


        weapon->update();


    }

    //sf::IntRect bodyRect = sf::IntRect(32*((int)xPosture),yPosture*32,32,32);
    sprite->setTextureRect(32*((int)xPosture),yPosture*32,32,32);
    sprite->setPosition(body->getPositionX(),body->getPositionY());
    //sprite.setRotation(body->getAngle());

    int xDir = 1- facingLeft*2;

    //sf::IntRect armRect = sf::IntRect(intX,0,9,8);
    armSprite->setTextureRect(intX,0,9,8);
    armSprite->setPosition(body->getPositionX()-xDifArm*xDir,armPosY);
    //armSprite.setRotation(body->getAngle());
    lookingUp = false;
}

int Character::getId()
{
    return id;
}

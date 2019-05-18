#include "Grenade.h"
#include <Level.h>
#include <motorSFML.h>

Grenade::Grenade(double posx, double posy)
{
    facingLeft = false;
    id = 3;
    texture = new Texture("img/grenade.png");
    sprite = new Sprite(*texture->getTexture());
    sprite->setOrigin(5,5);
    sprite->setTextureRect(0,0,10,11); //las medidas de la imagen son 32x16

    activated = false;

    sprite->setPosition(posx,posy);
}

void Grenade::createBody()
{
    id = 3;
    float posx = sprite->getPosition().x;
    float posy = sprite->getPosition().y;
    float width = sprite->getLocalBounds().width;
    float height = sprite->getLocalBounds().height;
    body = Physics2D::Instance()->createGrenadeBody(posx,posy,width);
    body->setUserData(this);
}

Grenade::~Grenade()
{
    Level* level = Level::instance();
    level->removeWeapon(this);
    delete body;
    delete sprite;
    delete texture;
}

bool Grenade::activate()
{
    if (!activated)
    {
        activated = true;
        grenadeClock.restart();
        sprite->setTextureRect(10,0,10,11);
        return true;
    }
    else
        return false;
}

bool Grenade::shoot()
{
    return activate();
}

bool Grenade::explode()
{
    Level* level = Level::instance();
    level->addBullet(new Bullet(sprite->getPosition().x,sprite->getPosition().y,rand() % 45 + (-22.5),75));
    level->addBullet(new Bullet(sprite->getPosition().x,sprite->getPosition().y,rand() % 45 + 22.5,75));
    level->addBullet(new Bullet(sprite->getPosition().x,sprite->getPosition().y,rand() % 45 + 45+22.5,75));
    level->addBullet(new Bullet(sprite->getPosition().x,sprite->getPosition().y,rand() % 45 + 45*2+22.5,75));
    level->addBullet(new Bullet(sprite->getPosition().x,sprite->getPosition().y,rand() % 45 + 45*3+22.5,75));
    level->addBullet(new Bullet(sprite->getPosition().x,sprite->getPosition().y,rand() % 45 + 45*4+22.5,75));
    level->addBullet(new Bullet(sprite->getPosition().x,sprite->getPosition().y,rand() % 45 + 45*5+22.5,75));
    level->addBullet(new Bullet(sprite->getPosition().x,sprite->getPosition().y,rand() % 45 + 45*6+22.5,75));

    return true;
}

void Grenade::update()
{
    int xDir = 1;
    if (facingLeft)
        xDir = -1;

    sprite->setScale(xDir,1);

    if (body != nullptr){
        sprite->setPosition(body->getPositionX(),body->getPositionY());
        sprite->setRotation(body->getAngle());
    }


    if (activated && grenadeClock.getElapsedTime().asSeconds() >= GRENADETIME)
    {
        explode();
        if (owner != nullptr)
            owner->dropWeapon();

        activated = false;
        delete this;
    }
}

void Grenade::draw()
{
    motorSFML::Instance()->draw(sprite->getSprite());
}

int Grenade::getId()
{
    return id;
}

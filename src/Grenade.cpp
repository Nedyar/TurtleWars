#include "Grenade.h"
#include <Level.h>

Grenade::Grenade(double posx, double posy)
{
    facingLeft = false;

    texture.loadFromFile("img/grenade.png");
    sprite.setTexture(texture);
    sprite.setOrigin(5,5);
    sprite.setTextureRect(sf::IntRect(0,0,10,11)); //las medidas de la imagen son 32x16

    activated = false;

    sprite.setPosition(posx,posy);
}

Grenade::~Grenade()
{
    //dtor
}

bool Grenade::activate()
{
    if (!activated)
    {
        activated = true;
        grenadeTimer.restart();
        sprite.setTextureRect(sf::IntRect(10,0,10,11));
        return true;
    }
    else
        return false;
}

bool Grenade::shoot()
{
    if (activate())
        return true;
    else
        return false;
}

bool Grenade::explode()
{
    Level* level = Level::instance(0);
    level->addBullet(new Bullet(sprite.getPosition().x,sprite.getPosition().y,rand() % 45 + (-22.5),75));
    level->addBullet(new Bullet(sprite.getPosition().x,sprite.getPosition().y,rand() % 45 + 22.5,75));
    level->addBullet(new Bullet(sprite.getPosition().x,sprite.getPosition().y,rand() % 45 + 45+22.5,75));
    level->addBullet(new Bullet(sprite.getPosition().x,sprite.getPosition().y,rand() % 45 + 45*2+22.5,75));
    level->addBullet(new Bullet(sprite.getPosition().x,sprite.getPosition().y,rand() % 45 + 45*3+22.5,75));
    level->addBullet(new Bullet(sprite.getPosition().x,sprite.getPosition().y,rand() % 45 + 45*4+22.5,75));
    level->addBullet(new Bullet(sprite.getPosition().x,sprite.getPosition().y,rand() % 45 + 45*5+22.5,75));
    level->addBullet(new Bullet(sprite.getPosition().x,sprite.getPosition().y,rand() % 45 + 45*6+22.5,75));

    return true;
}

void Grenade::update()
{
    int xDir = 1;
    if (facingLeft)
        xDir = -1;

    sprite.setScale(xDir,1);

    if (activated && grenadeTimer.getElapsedTime().asSeconds() >= GRENADETIME)
    {
        explode();
        if (owner != nullptr)
            owner->dropWeapon();
        Level* level = Level::instance(0);
        level->removeWeapon(this);
        activated = false;
        delete this;
    }
}

void Grenade::draw(sf::RenderWindow &app)
{
    app.draw(sprite);
}

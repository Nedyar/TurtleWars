#include "Bullet.h"
#include <Level.h>

Bullet::Bullet(double posx, double posy, double ang, double maxLen)
{
    bulletTexture.loadFromFile("img/bullet.png");
    bulletSprite.setTexture(bulletTexture);
    bulletSprite.setOrigin(0,bulletTexture.getSize().y/2);
    bulletSprite.setPosition(posx, posy);
    bulletSprite.setRotation(ang);

    posiniX=posx;
    posiniY=posy;

    angle = ang*M_PI/180;
    maxLength = maxLen;
}

void Bullet::update()
{
    bulletSprite.move(VEL*cos(angle), VEL*sin(angle));
    if(sqrt(pow(bulletSprite.getPosition().x-posiniX, 2)+pow(bulletSprite.getPosition().y-posiniY, 2))>=maxLength)
    {
        Level* level = Level::instance(0);
        level->removeBullet(this);
        delete this;
    }
}

void Bullet::draw(sf::RenderWindow &app)
{
    app.draw(bulletSprite);
}


Bullet::~Bullet()
{
    //dtor
}




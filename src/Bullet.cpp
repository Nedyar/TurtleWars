#include "Bullet.h"

Bullet::Bullet(double posx, double posy, double ang, double maxLen)
{
    bulletTexture.loadFromFile("img/bullet.png");
    bulletSprite.setTexture(bulletTexture);
    bulletSprite.setOrigin(0,16);
    sf::IntRect rect = sf::IntRect(46,0,50,32);
    bulletSprite.setTextureRect(rect);
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
}

void Bullet::draw(sf::RenderWindow &app)
{
    app.draw(bulletSprite);
}


Bullet::~Bullet()
{
    //dtor
}




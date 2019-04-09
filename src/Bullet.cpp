#include "Bullet.h"

Bullet::Bullet(double posx, double posy, double ang, double maxLen)
{

    bulletTexture.loadFromFile("img/bullet.png");
    bulletSprite.setTexture(bulletTexture);
    bulletSprite.setPosition(posx, posy);

    posiniX=posx;
    posiniY=posy;

    angle = ang*M_PI/180;
    maxLength = maxLen;

    vel=15;

}

void Bullet::update()
{
    if(sqrt(pow(bulletSprite.getPosition().x-posiniX, 2)+pow(bulletSprite.getPosition().y-posiniY, 2))<maxLength)
    {
        bulletSprite.move(vel*cos(angle), vel*sin(angle));
    }
    else //cuando ha llegado a su límite
    {
        //destruir bala
    }
}
void Bullet::render(sf::RenderWindow &app)
{
    app.draw(bulletSprite);
}


Bullet::~Bullet()
{
    //dtor
}




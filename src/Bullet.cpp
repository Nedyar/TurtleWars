#include "Bullet.h"

Bullet::Bullet(double posx, double posy, double ang, double maxLen)
{

    bulletTexture.loadFromFile("img/bullet.png");
    bulletSprite.setTexture(bulletTexture);
    bulletSprite.setPosition(posx, posy);

    angle = ang;
    maxLength = maxLen;

}

void Bullet::update()
{
    //Codigo
}
void Bullet::render(sf::RenderWindow &app)
{
    app.draw(bulletSprite);
}


Bullet::~Bullet()
{
    //dtor
}




#include "Gun.h"
#include <Level.h>

Gun::Gun(double posx, double posy)
{
    texture.loadFromFile("img/pistol.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,18,10)); //las medidas de la imagen son 72x10



    setpos(posx, posy);

    ammo=7;

    shootAnim=false;
}

void Gun::setpos(double posx, double posy)
{
    sprite.setPosition(posx, posy);
}

Gun::~Gun()
{
    //dtor
}

void Gun::update()
{
    if(shootAnim)
    {
        shootAnimation();
    }
}

void Gun::draw(sf::RenderWindow &app)
{
    app.draw(sprite);
//    app.draw(body.dameRec());
}

bool Gun::shoot()
{
    if (ammo > 0)
    {
        if(!shootAnim) //para que dispare al finalizar la animación de la pistola (hay colddown)
        {
            ammo--;
            shootAnim=true;

            Level* level = Level::instance(0);
            level->addBullet(new Bullet(sprite.getPosition().x,sprite.getPosition().y,rand() % 7 + -3,200));

            clockAnimation.restart();
            return true;
        }
        else
            return false;
    }
    else
    {
        return false;
    }
}

void Gun::shootAnimation()
{
    if(clockAnimation.getElapsedTime().asSeconds()<0.05)
    {
        sprite.setTextureRect(sf::IntRect(18,0,18,10)); //las medidas de la imagen son 72x10
    }
    else if(clockAnimation.getElapsedTime().asSeconds()<0.1)
    {
        sprite.setTextureRect(sf::IntRect(36,0,18,10));
    }
    else if(clockAnimation.getElapsedTime().asSeconds()<0.15)
    {
        sprite.setTextureRect(sf::IntRect(54,0,18,10));
    }
    else if(clockAnimation.getElapsedTime().asSeconds()<0.2)
    {
        sprite.setTextureRect(sf::IntRect(0,0,18,10));
        shootAnim=false;
    }


}

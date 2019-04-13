#include "Gun.h"
#include <Level.h>

Gun::Gun(double posx, double posy)
{
    facingLeft = false;

    texture.loadFromFile("img/pistol.png");
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x/8,texture.getSize().y/2);
    sprite.setTextureRect(sf::IntRect(0,0,18,10)); //las medidas de la imagen son 72x10
    sprite.setPosition(posx,posy);

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
    cout << "Empezamos update de gun" << endl;
    int xDir = 1;
    if (facingLeft)
        xDir = -1;

    sprite.setScale(xDir,1);

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
            int xOrientation = 0;
            int xDirection = 1;
            if (facingLeft) {
                xOrientation = 180;
                xDirection = -1;
            }

            ammo--;
            shootAnim=true;

            Level* level = Level::instance(0);
            level->addBullet(new Bullet(sprite.getPosition().x+(sprite.getLocalBounds().width/2)*xDirection,sprite.getPosition().y-3.1,rand() % 7 + -3 + xOrientation,200));

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

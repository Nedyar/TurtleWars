#include "Gun.h"

Gun::Gun(double posx, double posy)
{
    gunTexture.loadFromFile("img/pistol.png");
    gunSprite.setTexture(gunTexture);
    gunSprite.setTextureRect(sf::IntRect(0,0,18,10)); //las medidas de la imagen son 72x10

    setpos(posx, posy);

    ammo=7;

    shootAnim=false;
}

void Gun::setpos(double posx, double posy)
{
    gunSprite.setPosition(posx, posy);
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

void Gun::render(sf::RenderWindow &app)
{
    app.draw(gunSprite);
}

bool Gun::shoot()
{
    if (ammo > 0)
    {
        if(!shootAnim) //para que dispare al finalizar la animación de la pistola (hay colddown)
        {
            ammo--;
            shootAnim=true;
            cout << "Piu" << endl;
            clockAnimation.restart();
            return true;
        }
        else
            return false;
    }
    else
    {
        cout << "Sin municion" << endl;
        return false;
    }
}

void Gun::shootAnimation()
{
    if(clockAnimation.getElapsedTime().asSeconds()<0.5)
    {
        gunSprite.setTextureRect(sf::IntRect(18,0,18,10)); //las medidas de la imagen son 72x10
    }
    else if(clockAnimation.getElapsedTime().asSeconds()<1)
    {
        gunSprite.setTextureRect(sf::IntRect(36,0,18,10));
    }
    else if(clockAnimation.getElapsedTime().asSeconds()<1.5)
    {
        gunSprite.setTextureRect(sf::IntRect(54,0,18,10));
    }
    else if(clockAnimation.getElapsedTime().asSeconds()<2)
    {
        gunSprite.setTextureRect(sf::IntRect(0,0,18,10));
        shootAnim=false;
    }


}

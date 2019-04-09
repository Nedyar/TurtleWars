#include "Grenade.h"

Grenade::Grenade(double posx, double posy)
{
    grenadeTexture.loadFromFile("img/grenade.png");
    grenadeSprite.setTexture(grenadeTexture);
    grenadeSprite.setTextureRect(sf::IntRect(0,0,16,16)); //las medidas de la imagen son 32x16

    activated = false;
    grenadeTime = 5.0;

    grenadeSprite.setPosition(posx,posy);
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
        cout << "Sin anilla" << endl;
        grenadeSprite.setTextureRect(sf::IntRect(16,0,16,16));
        return true;
    }
    else
        return false;
}

bool Grenade::fire() //para comprobar si explota
{
    if (activated && grenadeTimer.getElapsedTime().asSeconds()>=grenadeTime)
    {
        if(explode())
            return true;
    }
    else
        return false;

    return false;
}

bool Grenade::shoot()
{
    if (!throwed)
    {
        if (!activate())
        {
            activate();
            return true;
        }
    }
    return false;
}

bool Grenade::explode()
{
    cout << "Booooooom" << endl;
    return true; //aqui debemos de crear las balas y llamar a destrir esta granada
}

void Grenade::update()
{
    fire();
}

void Grenade::render(sf::RenderWindow &app)
{
    app.draw(grenadeSprite);
}

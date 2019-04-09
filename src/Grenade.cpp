#include "Grenade.h"

Grenade::Grenade(double posx, double posy)
{
    texture.loadFromFile("img/grenade.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,16,16)); //las medidas de la imagen son 32x16

    activated = false;
    grenadeTime = 5.0;

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
        cout << "Sin anilla" << endl;
        sprite.setTextureRect(sf::IntRect(16,0,16,16));
        return true;
    }
    else
        return false;
}

bool Grenade::shoot()
{

    if (!activate())
    {
        activate();
        return true;
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

}

void Grenade::draw(sf::RenderWindow &app)
{
    app.draw(sprite);
}

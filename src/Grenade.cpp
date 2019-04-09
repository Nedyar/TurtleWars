#include "Grenade.h"
#include <Level.h>

Grenade::Grenade(double posx, double posy)
{
    texture.loadFromFile("img/grenade.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,16,16)); //las medidas de la imagen son 32x16

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
        cout << "Sin anilla" << endl;
        sprite.setTextureRect(sf::IntRect(16,0,16,16));
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
    int XSUM = 4;
    int YSUM = 6;
    level->addBullet(new Bullet(sprite.getPosition().x+XSUM,sprite.getPosition().y+YSUM,rand() % 45 + (-22.5),75));
    level->addBullet(new Bullet(sprite.getPosition().x+XSUM,sprite.getPosition().y+YSUM,rand() % 45 + 22.5,75));
    level->addBullet(new Bullet(sprite.getPosition().x+XSUM,sprite.getPosition().y+YSUM,rand() % 45 + 45+22.5,75));
    level->addBullet(new Bullet(sprite.getPosition().x+XSUM,sprite.getPosition().y+YSUM,rand() % 45 + 45*2+22.5,75));
    level->addBullet(new Bullet(sprite.getPosition().x+XSUM,sprite.getPosition().y+YSUM,rand() % 45 + 45*3+22.5,75));
    level->addBullet(new Bullet(sprite.getPosition().x+XSUM,sprite.getPosition().y+YSUM,rand() % 45 + 45*4+22.5,75));
    level->addBullet(new Bullet(sprite.getPosition().x+XSUM,sprite.getPosition().y+YSUM,rand() % 45 + 45*5+22.5,75));
    level->addBullet(new Bullet(sprite.getPosition().x+XSUM,sprite.getPosition().y+YSUM,rand() % 45 + 45*6+22.5,75));
    cout << "Booooooom" << endl;

    return true; //aqui debemos de crear las balas y llamar a destrir esta granada
}

void Grenade::update()
{
    if (activated && grenadeTimer.getElapsedTime().asSeconds() >= GRENADETIME) {
        explode();
        Level* level = Level::instance(0);
        level->removeWeapon(this);
        activated = false;
    }
}

void Grenade::draw(sf::RenderWindow &app)
{
    app.draw(sprite);
}

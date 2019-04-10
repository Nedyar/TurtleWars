#include "ShotGun.h"
#include <Level.h>

ShotGun::ShotGun(double posx, double posy)
{
    texture.loadFromFile("img/shotgun.png");
    sprite.setTexture(texture);

    shotGunLoaderTexture.loadFromFile("img/shotgunLoader.png");
    shotGunLoaderSprite.setTexture(shotGunLoaderTexture);
    shotGunLoaderSprite.setTextureRect(sf::IntRect(0,0,8,8));

    ammo=3;
    shooted = false;
    shootAnim = false;
    shootAnimBack = false;

    sprite.setPosition(posx,posy);
    shotGunLoaderSprite.setPosition(posx+20,posy+14);
}

ShotGun::~ShotGun()
{
    //dtor
}

bool ShotGun::reload()
{
    if (ammo > 0 && shooted)
    {
        shooted = false;
        clockAnimation.restart();
        shootAnim = true;
        shootAnimBack = true;
        return true;
    }
    else
        return false;
}

void ShotGun::setpos(double posx, double posy)
{
    shotGunLoaderSprite.setPosition(posx, posy);
}

bool ShotGun::shoot()
{

    if (ammo > 0)
    {
        if (!reload()&&!shootAnimBack&&!shootAnim)
        {
            shooted = true;
            ammo--;
            Level* level = Level::instance(0);
            level->addBullet(new Bullet(sprite.getPosition().x+texture.getSize().x,sprite.getPosition().y+10,rand() % 6 + 9,100));
            level->addBullet(new Bullet(sprite.getPosition().x+texture.getSize().x,sprite.getPosition().y+10,rand() % 6 + 3,100));
            level->addBullet(new Bullet(sprite.getPosition().x+texture.getSize().x,sprite.getPosition().y+10,rand() % 6 + (-3),100));
            level->addBullet(new Bullet(sprite.getPosition().x+texture.getSize().x,sprite.getPosition().y+10,rand() % 6 + (-9),100));
            level->addBullet(new Bullet(sprite.getPosition().x+texture.getSize().x,sprite.getPosition().y+10,rand() % 6 + (-15),100));
            return true;
        }
    }
    /*else
    {
        cout << "Sin municion" << endl;
    }*/
    return false;

}

void ShotGun::update()
{
    if(shootAnim)
    {
        shootAnimation();
    }
}

void ShotGun::draw(sf::RenderWindow &app)
{
    app.draw(sprite);
    app.draw(shotGunLoaderSprite);
}

void ShotGun::shootAnimation()
{
    if(clockAnimation.getElapsedTime().asSeconds()<0.25 && shootAnimBack)
    {
        shotGunLoaderSprite.setTextureRect(sf::IntRect(8,0,8,8));
        setpos(shotGunLoaderSprite.getPosition().x-3, shotGunLoaderSprite.getPosition().y);
        shootAnimBack=false;
    }
    else if(clockAnimation.getElapsedTime().asSeconds()<0.5 && clockAnimation.getElapsedTime().asSeconds()>0.25 && !shootAnimBack)
    {
        shotGunLoaderSprite.setTextureRect(sf::IntRect(0,0,8,8));
        setpos(shotGunLoaderSprite.getPosition().x+3, shotGunLoaderSprite.getPosition().y);
        shootAnim=false;
    }
}

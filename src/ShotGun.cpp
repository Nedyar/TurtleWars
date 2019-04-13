#include "ShotGun.h"
#include <Level.h>

ShotGun::ShotGun(double posx, double posy)
{
    facingLeft = false;

    texture.loadFromFile("img/shotgun.png");
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x/2,texture.getSize().y/2);

    shotGunLoaderTexture.loadFromFile("img/shotgunLoader.png");
    shotGunLoaderSprite.setTexture(shotGunLoaderTexture);
    shotGunLoaderSprite.setOrigin(shotGunLoaderTexture.getSize().x/4,shotGunLoaderTexture.getSize().y/2);
    shotGunLoaderSprite.setTextureRect(sf::IntRect(0,0,8,8));

    ammo=3;
    shooted = false;
    shootAnim = false;
    shootAnimBack = false;

    sprite.setPosition(posx,posy);
    shotGunLoaderSprite.setPosition(posx+2,posy);
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

bool ShotGun::shoot()
{
    if (ammo > 0)
    {
        if (!reload()&&!shootAnimBack&&!shootAnim)
        {
            int xOrientation = 0;
            int xDirection = 1;
            if (facingLeft) {
                xOrientation = 180;
                xDirection = -1;
            }

            shooted = true;
            ammo--;
            Level* level = Level::instance(0);
            level->addBullet(new Bullet(sprite.getPosition().x+(sprite.getLocalBounds().width/2)*xDirection,sprite.getPosition().y-2.8,(rand() % 6 + 9)+xOrientation,100));
            level->addBullet(new Bullet(sprite.getPosition().x+(sprite.getLocalBounds().width/2)*xDirection,sprite.getPosition().y-2.8,(rand() % 6 + 3)+xOrientation,100));
            level->addBullet(new Bullet(sprite.getPosition().x+(sprite.getLocalBounds().width/2)*xDirection,sprite.getPosition().y-2.8,(rand() % 6 + (-3))+xOrientation,100));
            level->addBullet(new Bullet(sprite.getPosition().x+(sprite.getLocalBounds().width/2)*xDirection,sprite.getPosition().y-2.8,(rand() % 6 + (-9))+xOrientation,100));
            level->addBullet(new Bullet(sprite.getPosition().x+(sprite.getLocalBounds().width/2)*xDirection,sprite.getPosition().y-2.8,(rand() % 6 + (-15))+xOrientation,100));
            return true;
        }
    }
    return false;
}

void ShotGun::update()
{
    cout << "Empezamos update de shotgun" << endl;
    int xDir = 1;
    if (facingLeft)
        xDir = -1;

    sprite.setScale(xDir,1);
    shotGunLoaderSprite.setScale(xDir,1);

    shotGunLoaderSprite.setPosition(sprite.getPosition().x+1.8*xDir,sprite.getPosition().y+1.2);
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
    int xDir = 1;
    if (facingLeft)
        xDir = -1;

    if(clockAnimation.getElapsedTime().asSeconds()<0.25 && shootAnimBack)
    {
        shotGunLoaderSprite.setTextureRect(sf::IntRect(8,0,8,8));
        shotGunLoaderSprite.setPosition(shotGunLoaderSprite.getPosition().x-3*xDir, shotGunLoaderSprite.getPosition().y);
        shootAnimBack=false;
    }
    else if(clockAnimation.getElapsedTime().asSeconds()<0.5 && clockAnimation.getElapsedTime().asSeconds()>0.25 && !shootAnimBack)
    {
        shotGunLoaderSprite.setTextureRect(sf::IntRect(0,0,8,8));
        shotGunLoaderSprite.setPosition(shotGunLoaderSprite.getPosition().x+3*xDir, shotGunLoaderSprite.getPosition().y);
        shootAnim=false;
    }
}

#include "ShotGun.h"
#include <Level.h>

ShotGun::ShotGun(double posx, double posy)
{
    facingLeft = false;
    id = 3;
    texture = new Texture("img/shotgun.png");
    sprite = new Sprite(*texture->getTexture());
    sprite->setOrigin(texture->getSize().x/2,texture->getSize().y/2);

    shotGunLoaderTexture = new Texture("img/shotgunLoader.png");
    shotGunLoaderSprite = new Sprite(*shotGunLoaderTexture->getTexture());
    shotGunLoaderSprite->setOrigin(shotGunLoaderTexture->getSize().x/4,shotGunLoaderTexture->getSize().y/2);
    shotGunLoaderSprite->setTextureRect(0,0,8,8);

    ammo=2;
    shooted = false;
    shootAnim = false;
    shootAnimBack = false;

    sprite->setPosition(posx,posy);

    shotGunLoaderSprite->setPosition(posx+2,posy);

    chargeSound();

    shotGunLoaderSprite->setPosition(posx+2,posy+1);

    flashTexture = new Texture("img/weaponSmoke.png");
    flashSprite = new Sprite(*flashTexture->getTexture());
    flashSprite->setOrigin(8,8);

    smokeTexture = new Texture("img/barrelSmoke.png");
    smokeSprite = new Sprite(*smokeTexture->getTexture());
    smokeSprite->setOrigin(4,16);

}

void ShotGun::createBody()
{
    id = 3;
    float posx = sprite->getPosition().x;
    float posy = sprite->getPosition().y;
    float width = sprite->getLocalBounds().width;
    float height = sprite->getLocalBounds().height;
    body = Physics2D::Instance()->createWeaponBody(posx,posy,width,height);;
    body->setUserData(this);
}

ShotGun::~ShotGun()
{
    Level* level = Level::instance();
    level->removeWeapon(this);
    delete body;
    delete shotGunLoaderSprite;
    delete shotGunLoaderTexture;
    delete sprite;
    delete texture;
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
            int xOrientation = 0 + facingLeft*180;
            int xDirection = 1 - facingLeft*2;

            shooted = true;
            ammo--;
            float mod = 0;
            if (owner->body->getBody()->GetLinearVelocity().x!=0)
                mod += 6;
            Level* level = Level::instance();
            level->addBullet(new Bullet(sprite->getPosition().x+(mod+sprite->getLocalBounds().width/2)*xDirection,sprite->getPosition().y-2.8,(rand() % 6 + 9)+xOrientation,100));
            level->addBullet(new Bullet(sprite->getPosition().x+(mod+sprite->getLocalBounds().width/2)*xDirection,sprite->getPosition().y-2.8,(rand() % 6 + 3)+xOrientation,100));
            level->addBullet(new Bullet(sprite->getPosition().x+(mod+sprite->getLocalBounds().width/2)*xDirection,sprite->getPosition().y-2.8,(rand() % 6 + (-3))+xOrientation,100));
            level->addBullet(new Bullet(sprite->getPosition().x+(mod+sprite->getLocalBounds().width/2)*xDirection,sprite->getPosition().y-2.8,(rand() % 6 + (-9))+xOrientation,100));
            level->addBullet(new Bullet(sprite->getPosition().x+(mod+sprite->getLocalBounds().width/2)*xDirection,sprite->getPosition().y-2.8,(rand() % 6 + (-15))+xOrientation,100));

            shotgunsound.play();

            smoking=true;
            smokeClock.restart();

            flashing=true;
            flashClock.restart();

            return true;
        }
    }
    return false;
}

void ShotGun::update()
{
    int xDir = 1 - facingLeft*2;

    sprite->setScale(xDir,1);
    shotGunLoaderSprite->setScale(xDir,1);

    shotGunLoaderSprite->setPosition(sprite->getPosition().x+1.8*xDir,sprite->getPosition().y+1.2);
    if(shootAnim)
    {
        shootAnimation();
    }

    if(smoking)
    {
        smokeAnimation();
    }

    if(flashing)
    {
        flashAnim();
    }

    if (body != nullptr)
        sprite->setPosition(body->getPositionX(),body->getPositionY());

    if (ammo == 0 && owner == nullptr && clock.getElapsedTime().asSeconds() > 2)
        delete this;
}

void ShotGun::draw()
{
    motorSFML::Instance()->draw(sprite->getSprite());
    motorSFML::Instance()->draw(shotGunLoaderSprite->getSprite());

    if(smoking && smokeClock.getElapsedTime().asSeconds()>0.5)
        motorSFML::Instance()->draw(smokeSprite->getSprite());

    if(flashing)
        motorSFML::Instance()->draw(flashSprite->getSprite());
}

void ShotGun::shootAnimation()
{

    int xDir = 1;
    if (facingLeft)
        xDir = -1;

    if(clockAnimation.getElapsedTime().asSeconds()<0.25 && shootAnimBack)
    {
        shotGunLoaderSprite->setTextureRect(8,0,8,8);
        shotGunLoaderSprite->setPosition(shotGunLoaderSprite->getPosition().x-3*xDir, shotGunLoaderSprite->getPosition().y);
        shootAnimBack=false;
    }
    else if(clockAnimation.getElapsedTime().asSeconds()<0.5 && clockAnimation.getElapsedTime().asSeconds()>0.25 && !shootAnimBack)
    {
        shotGunLoaderSprite->setTextureRect(0,0,8,8);
        shotGunLoaderSprite->setPosition(shotGunLoaderSprite->getPosition().x+3*xDir, shotGunLoaderSprite->getPosition().y);
        shootAnim=false;
    }
}

void ShotGun::smokeAnimation()
{
    if(!facingLeft){
        smokeSprite->setPosition(sprite->getPosition().x+13, sprite->getPosition().y-10);
    }else{
        smokeSprite->setPosition(sprite->getPosition().x-10, sprite->getPosition().y-10);
    }

    if(smokeClock.getElapsedTime().asSeconds()<0.5)
    {
        smokeSprite->setTextureRect(0,0,8,32);
    }
    else if(smokeClock.getElapsedTime().asSeconds()<0.8)
    {
        smokeSprite->setTextureRect(8,0,8,32);
    }
    else if(smokeClock.getElapsedTime().asSeconds()<1.1)
    {
        smokeSprite->setTextureRect(16,0,8,32);
    }
    else if(smokeClock.getElapsedTime().asSeconds()<1.4)
    {
        smokeSprite->setTextureRect(24,0,8,32);
    }
    else if(smokeClock.getElapsedTime().asSeconds()<1.7){
        smoking=false;
    }
}

void ShotGun::flashAnim()
{
    if(!facingLeft){
        flashSprite->setPosition(sprite->getPosition().x+19, sprite->getPosition().y-3);
        flashSprite->setRotation(0);
    }else{
        flashSprite->setPosition(sprite->getPosition().x-19, sprite->getPosition().y-2);
        flashSprite->setRotation(180);
        }

    if(flashClock.getElapsedTime().asSeconds()<0.05)
    {
        flashSprite->setTextureRect(0,0,16,16);
    }
    else if(flashClock.getElapsedTime().asSeconds()<0.15)
    {
        flashSprite->setTextureRect(16,0,16,16);
    }

    else if(flashClock.getElapsedTime().asSeconds()<0.6)
    {
        flashing=false;
    }
}

int ShotGun::getId()
{
    return id;
}

void ShotGun::chargeSound(){

    motorSFML::Instance()->loadSound("./sounds/shotgunFire2.wav",sbshotgun,shotgunsound);

}

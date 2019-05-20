#include "Gun.h"
#include <Level.h>

Gun::Gun(double posx, double posy)
{
    facingLeft = false;
    id = 3;
    texture = new Texture("img/pistol.png");
    sprite = new Sprite(*texture->getTexture());
    sprite->setOrigin(texture->getSize().x/8,texture->getSize().y/2);
    sprite->setTextureRect(0,0,18,10); //las medidas de la imagen son 72x10
    sprite->setPosition(posx,posy);

    flashTexture = new Texture("img/weaponSmoke.png");
    flashSprite = new Sprite(*flashTexture->getTexture());
    flashSprite->setOrigin(8,8);

    smokeTexture = new Texture("img/barrelSmoke.png");
    smokeSprite = new Sprite(*smokeTexture->getTexture());
    smokeSprite->setOrigin(4,16);

    ammo=7;

    shootAnim=false;

    chargeSound();
}

void Gun::createBody()
{
    id = 3;
    float posx = sprite->getPosition().x;
    float posy = sprite->getPosition().y;
    float width = sprite->getLocalBounds().width;
    float height = sprite->getLocalBounds().height;
    body = Physics2D::Instance()->createWeaponBody(posx,posy,width,height);
    body->setUserData(this);
}

Gun::~Gun()
{
    Level* level = Level::instance();
    level->removeWeapon(this);
    delete body;
    delete sprite;
    delete texture;
}

void Gun::update()
{
    int xDir = 1 - facingLeft*2;

    sprite->setScale(xDir,1);

    if(shootAnim)
    {
        shootAnimation();
    }

    if(smoking)
    {
        smokeAnimation();
    }

    if (body != nullptr)
        sprite->setPosition(body->getPositionX(),body->getPositionY());


    if (ammo == 0 && owner == nullptr && clock.getElapsedTime().asSeconds() > 2)
        delete this;
}

void Gun::draw()
{
    motorSFML::Instance()->draw(sprite->getSprite());
    if(shootAnim)
        motorSFML::Instance()->draw(flashSprite->getSprite());

    if(smoking && smokeClock.getElapsedTime().asSeconds()>0.5)
        motorSFML::Instance()->draw(smokeSprite->getSprite());
}

bool Gun::shoot()
{
    if (ammo > 0)
    {
        if(!shootAnim) //para que dispare al finalizar la animación de la pistola (hay colddown)
        {
            int xOrientation = 0 + facingLeft*180;//Calcular el angulo de la bala
            int xDirection = 1 - facingLeft*2;//Calcular direccion del sprite 1 = derecha; -1 = izquierda

            ammo--;
            shootAnim=true;

            int modX = 0;
            if (owner->body->getBody()->GetLinearVelocity().x!=0)
                modX += 5;
            float posx = sprite->getPosition().x+(modX+sprite->getLocalBounds().width/2)*xDirection;
            float posy = sprite->getPosition().y-3.1;
            float ang = rand() % 7 + -3 + xOrientation;
            Level::instance()->addBullet(new Bullet(posx,posy,ang,200));//debe pasar la direccion del arma

            clockAnimation.restart();

            pistolsound.play();


            smoking=true;
            smokeClock.restart();
            
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
    if(!facingLeft){
        flashSprite->setPosition(sprite->getPosition().x+15, sprite->getPosition().y-4);
        flashSprite->setRotation(0);
    }else{
        flashSprite->setPosition(sprite->getPosition().x-15, sprite->getPosition().y-4);
        flashSprite->setRotation(180);
        }
    if(clockAnimation.getElapsedTime().asSeconds()<0.05)
    {
        sprite->setTextureRect(18,0,18,10);//las medidas de la imagen son 72x10
        flashSprite->setTextureRect(0,0,16,16);
    }
    else if(clockAnimation.getElapsedTime().asSeconds()<0.1)
    {
        sprite->setTextureRect(36,0,18,10);
    }
    else if(clockAnimation.getElapsedTime().asSeconds()<0.15)
    {
        sprite->setTextureRect(54,0,18,10);
        flashSprite->setTextureRect(16,0,16,16);
    }
    else if(clockAnimation.getElapsedTime().asSeconds()<0.2)
    {
        sprite->setTextureRect(0,0,18,10);
        shootAnim=false;
    }


}

void Gun::smokeAnimation()
{
    if(!facingLeft){
        smokeSprite->setPosition(sprite->getPosition().x+10, sprite->getPosition().y-10);
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

int Gun::getId()
{
    return id;
}

void Gun::chargeSound(){

    motorSFML::Instance()->loadSound("./sounds/pistol.wav",sbpistol,pistolsound);

}

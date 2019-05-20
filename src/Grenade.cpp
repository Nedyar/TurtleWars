#include "Grenade.h"
#include <Level.h>
#include <motorSFML.h>

Grenade::Grenade(double posx, double posy)
{
    facingLeft = false;
    id = 3;
    texture = new Texture("img/grenade.png");
    sprite = new Sprite(*texture->getTexture());
    sprite->setOrigin(5,5);
    sprite->setTextureRect(0,0,10,11); //las medidas de la imagen son 32x16

    explosionTexture = new Texture("img/explosion.png");

    explosionSprite1 = new Sprite(*explosionTexture->getTexture());
    explosionSprite2 = new Sprite(*explosionTexture->getTexture());
    explosionSprite3 = new Sprite(*explosionTexture->getTexture());
    explosionSprite4 = new Sprite(*explosionTexture->getTexture());
    explosionSprite5 = new Sprite(*explosionTexture->getTexture());
    explosionSprite6 = new Sprite(*explosionTexture->getTexture());

    explosionSprite1->setOrigin(32,32);
    explosionSprite2->setOrigin(32,32);
    explosionSprite3->setOrigin(32,32);
    explosionSprite4->setOrigin(32,32);
    explosionSprite5->setOrigin(32,32);
    explosionSprite6->setOrigin(32,32);

    explosionSprite1->setTextureRect(0,0,64,64);
    explosionSprite2->setTextureRect(0,0,64,64);
    explosionSprite3->setTextureRect(0,0,64,64);
    explosionSprite4->setTextureRect(0,0,64,64);
    explosionSprite5->setTextureRect(0,0,64,64);
    explosionSprite6->setTextureRect(0,0,64,64);


    activated = false;

    sprite->setPosition(posx,posy);

    chargeSound();

}

void Grenade::createBody()
{
    id = 3;
    float posx = sprite->getPosition().x;
    float posy = sprite->getPosition().y;
    float width = sprite->getLocalBounds().width;
    float height = sprite->getLocalBounds().height;
    body = Physics2D::Instance()->createGrenadeBody(posx,posy,width);
    body->setUserData(this);
}

Grenade::~Grenade()
{
    Level* level = Level::instance();
    level->removeWeapon(this);
    delete body;
    delete sprite;
    delete texture;
}

bool Grenade::activate()
{
    if (!activated)
    {
        activated = true;
        grenadeClock.restart();
        sprite->setTextureRect(10,0,10,11);
        return true;
    }
    else
        return false;
}

bool Grenade::shoot()
{
    return activate();
}

bool Grenade::explode()
{
    Level* level = Level::instance();
    level->addBullet(new Bullet(sprite->getPosition().x,sprite->getPosition().y,rand() % 45 + (-22.5),75));
    level->addBullet(new Bullet(sprite->getPosition().x,sprite->getPosition().y,rand() % 45 + 22.5,75));
    level->addBullet(new Bullet(sprite->getPosition().x,sprite->getPosition().y,rand() % 45 + 45+22.5,75));
    level->addBullet(new Bullet(sprite->getPosition().x,sprite->getPosition().y,rand() % 45 + 45*2+22.5,75));
    level->addBullet(new Bullet(sprite->getPosition().x,sprite->getPosition().y,rand() % 45 + 45*3+22.5,75));
    level->addBullet(new Bullet(sprite->getPosition().x,sprite->getPosition().y,rand() % 45 + 45*4+22.5,75));
    level->addBullet(new Bullet(sprite->getPosition().x,sprite->getPosition().y,rand() % 45 + 45*5+22.5,75));
    level->addBullet(new Bullet(sprite->getPosition().x,sprite->getPosition().y,rand() % 45 + 45*6+22.5,75));

    grenadesound.play();

    animationClock.restart();
    exploded = true;
    randomAnimation1 = (rand() % 3)/10;
    randomAnimation2 = (rand() % 3)/10;
    randomAnimation3 = (rand() % 3)/10;
    randomAnimation4 = (rand() % 3)/10;
    randomAnimation5 = (rand() % 3)/10;
    randomAnimation6 = (rand() % 3)/10;

    int randomPositionX = rand() % 30 + sprite->getPosition().x-15;
    int randomPositionY = rand() % 30 + sprite->getPosition().y-15;
    explosionSprite1->setPosition(randomPositionX,randomPositionY);

    randomPositionX = rand() % 30 + sprite->getPosition().x-15;
    randomPositionY = rand() % 30 + sprite->getPosition().y-15;
    explosionSprite2->setPosition(randomPositionX,randomPositionY);

    randomPositionX = rand() % 30 + sprite->getPosition().x-15;
    randomPositionY = rand() % 30 + sprite->getPosition().y-15;
    explosionSprite3->setPosition(randomPositionX,randomPositionY);

    randomPositionX = rand() % 30 + sprite->getPosition().x-15;
    randomPositionY = rand() % 30 + sprite->getPosition().y-15;
    explosionSprite4->setPosition(randomPositionX,randomPositionY);

    randomPositionX = rand() % 30 + sprite->getPosition().x-15;
    randomPositionY = rand() % 30 + sprite->getPosition().y-15;
    explosionSprite5->setPosition(randomPositionX,randomPositionY);

    randomPositionX = rand() % 30 + sprite->getPosition().x-15;
    randomPositionY = rand() % 30 + sprite->getPosition().y-15;
    explosionSprite6->setPosition(randomPositionX,randomPositionY);

    return true;
}

void Grenade::update()
{
    if(exploded){
        explosionAnimation();
    }else{

        int xDir = 1;
        if (facingLeft)
            xDir = -1;

        sprite->setScale(xDir,1);

        if (body != nullptr){
            sprite->setPosition(body->getPositionX(),body->getPositionY());
            sprite->setRotation(body->getAngle());
        }


        if (activated && grenadeClock.getElapsedTime().asSeconds() >= GRENADETIME)
        {
            explode();
        }
    }
}

void Grenade::explosionAnimation(){

    if(animationClock.getElapsedTime().asSeconds()>randomAnimation1){
        if(animationClock.getElapsedTime().asSeconds()<0.1+randomAnimation1)
            explosionSprite1->setTextureRect(64,0,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.2+randomAnimation1)
            explosionSprite1->setTextureRect(128,0,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.3+randomAnimation1)
            explosionSprite1->setTextureRect(192,0,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.4+randomAnimation1)
            explosionSprite1->setTextureRect(0,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.5+randomAnimation1)
            explosionSprite1->setTextureRect(64,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.6+randomAnimation1)
            explosionSprite1->setTextureRect(128,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.7+randomAnimation1)
            explosionSprite1->setTextureRect(192,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.8+randomAnimation1)
            explosionSprite1->setTextureRect(0,128,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.9+randomAnimation1)
            explosionSprite1->setTextureRect(64,128,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<1+randomAnimation1)
            explosionSprite1->setTextureRect(64,192,64,64);
    }

    if(animationClock.getElapsedTime().asSeconds()>randomAnimation2){
        if(animationClock.getElapsedTime().asSeconds()<0.1+randomAnimation2)
            explosionSprite2->setTextureRect(64,0,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.2+randomAnimation2)
            explosionSprite2->setTextureRect(128,0,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.3+randomAnimation2)
            explosionSprite2->setTextureRect(192,0,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.4+randomAnimation2)
            explosionSprite2->setTextureRect(0,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.5+randomAnimation2)
            explosionSprite2->setTextureRect(64,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.6+randomAnimation2)
            explosionSprite2->setTextureRect(128,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.7+randomAnimation2)
            explosionSprite2->setTextureRect(192,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.8+randomAnimation2)
            explosionSprite2->setTextureRect(0,128,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.9+randomAnimation2)
            explosionSprite2->setTextureRect(64,128,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<1+randomAnimation2)
            explosionSprite2->setTextureRect(64,192,64,64);
    }
    if(animationClock.getElapsedTime().asSeconds()>randomAnimation3){
        if(animationClock.getElapsedTime().asSeconds()<0.1+randomAnimation3)
            explosionSprite3->setTextureRect(64,0,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.2+randomAnimation3)
            explosionSprite3->setTextureRect(128,0,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.3+randomAnimation3)
            explosionSprite3->setTextureRect(192,0,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.4+randomAnimation3)
            explosionSprite3->setTextureRect(0,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.5+randomAnimation3)
            explosionSprite3->setTextureRect(64,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.6+randomAnimation3)
            explosionSprite3->setTextureRect(128,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.7+randomAnimation3)
            explosionSprite3->setTextureRect(192,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.8+randomAnimation3)
            explosionSprite3->setTextureRect(0,128,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.9+randomAnimation3)
            explosionSprite3->setTextureRect(64,128,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<1+randomAnimation3)
            explosionSprite3->setTextureRect(64,192,64,64);
    }
    if(animationClock.getElapsedTime().asSeconds()>randomAnimation4){
        if(animationClock.getElapsedTime().asSeconds()<0.1+randomAnimation4)
            explosionSprite4->setTextureRect(64,0,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.2+randomAnimation4)
            explosionSprite4->setTextureRect(128,0,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.3+randomAnimation4)
            explosionSprite4->setTextureRect(192,0,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.4+randomAnimation4)
            explosionSprite4->setTextureRect(0,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.5+randomAnimation4)
            explosionSprite4->setTextureRect(64,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.6+randomAnimation4)
            explosionSprite4->setTextureRect(128,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.7+randomAnimation4)
            explosionSprite4->setTextureRect(192,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.8+randomAnimation4)
            explosionSprite4->setTextureRect(0,128,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.9+randomAnimation4)
            explosionSprite4->setTextureRect(64,128,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<1+randomAnimation4)
            explosionSprite4->setTextureRect(64,192,64,64);
    }
    if(animationClock.getElapsedTime().asSeconds()>randomAnimation5){
        if(animationClock.getElapsedTime().asSeconds()<0.1+randomAnimation5)
            explosionSprite5->setTextureRect(64,0,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.2+randomAnimation5)
            explosionSprite5->setTextureRect(128,0,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.3+randomAnimation5)
            explosionSprite5->setTextureRect(192,0,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.4+randomAnimation5)
            explosionSprite5->setTextureRect(0,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.5+randomAnimation5)
            explosionSprite5->setTextureRect(64,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.6+randomAnimation5)
            explosionSprite5->setTextureRect(128,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.7+randomAnimation5)
            explosionSprite5->setTextureRect(192,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.8+randomAnimation5)
            explosionSprite5->setTextureRect(0,128,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.9+randomAnimation5)
            explosionSprite5->setTextureRect(64,128,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<1+randomAnimation5)
            explosionSprite5->setTextureRect(64,192,64,64);
    }
    if(animationClock.getElapsedTime().asSeconds()>randomAnimation6){
        if(animationClock.getElapsedTime().asSeconds()<0.1+randomAnimation6)
            explosionSprite6->setTextureRect(64,0,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.2+randomAnimation6)
            explosionSprite6->setTextureRect(128,0,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.3+randomAnimation6)
            explosionSprite6->setTextureRect(192,0,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.4+randomAnimation6)
            explosionSprite6->setTextureRect(0,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.5+randomAnimation6)
            explosionSprite6->setTextureRect(64,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.6+randomAnimation6)
            explosionSprite6->setTextureRect(128,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.7+randomAnimation6)
            explosionSprite6->setTextureRect(192,64,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.8+randomAnimation6)
            explosionSprite6->setTextureRect(0,128,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<0.9+randomAnimation6)
            explosionSprite6->setTextureRect(64,128,64,64);

        else if(animationClock.getElapsedTime().asSeconds()<1+randomAnimation6)
            explosionSprite6->setTextureRect(64,192,64,64);
    }
    if(animationClock.getElapsedTime().asSeconds()>1+0.3){
        if (owner != nullptr)
                owner->dropWeapon();

            activated = false;
            delete this;

    }

}

void Grenade::draw()
{
    if(!exploded)
        motorSFML::Instance()->draw(sprite->getSprite());
    else{
        motorSFML::Instance()->draw(explosionSprite1->getSprite());
        motorSFML::Instance()->draw(explosionSprite2->getSprite());
        motorSFML::Instance()->draw(explosionSprite3->getSprite());
        motorSFML::Instance()->draw(explosionSprite4->getSprite());
        motorSFML::Instance()->draw(explosionSprite5->getSprite());
        motorSFML::Instance()->draw(explosionSprite6->getSprite());
    }

}

int Grenade::getId()
{
    return id;
}

void Grenade::chargeSound()
{

    motorSFML::Instance()->loadSound("./sounds/grenadeFire.wav",sbgrenade,grenadesound);

}


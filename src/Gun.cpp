#include "Gun.h"
#include <Level.h>

Gun::Gun(double posx, double posy)
{
    facingLeft = false;
    id = 3;
    texture.loadFromFile("img/pistol.png");
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x/8,texture.getSize().y/2);
    sprite.setTextureRect(sf::IntRect(0,0,18,10)); //las medidas de la imagen son 72x10
    sprite.setPosition(posx,posy);

    ammo=7;

    shootAnim=false;
}

void Gun::createBody()
{
    id = 3;
    float posx = sprite.getPosition().x;
    float posy = sprite.getPosition().y;
    float width = sprite.getLocalBounds().width;
    float height = sprite.getLocalBounds().height;
    body = Physics2D::Instance()->createWeaponBody(posx,posy,width,height);
    body->setUserData(this);
}

void Gun::deleteBody()
{
    delete body;
    body = nullptr;
}

void Gun::setXVelocity(float velocity)
{
    body->getBody()->SetLinearVelocity((b2Vec2(velocity,body->getBody()->GetLinearVelocity().y)));
}

void Gun::setpos(double posx, double posy)
{
    sprite.setPosition(posx, posy);
}

Gun::~Gun()
{
    Level* level = Level::instance(0);
    level->removeWeapon(this);
    delete body;
}

void Gun::update()
{
    int xDir = 1;
    if (facingLeft)
        xDir = -1;

    sprite.setScale(xDir,1);

    if(shootAnim)
    {
        shootAnimation();
    }

    if (body != nullptr)
        sprite.setPosition(body->getPositionX(),body->getPositionY());

    /* Crear metodo para realizar esto al tocar el suelo o al pasar un tiempo
    if (ammo == 0 && owner == nullptr)
        delete this;*/
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
            int xOrientation = 0 + facingLeft*180;
            int xDirection = 1 - facingLeft*2;

            ammo--;
            shootAnim=true;


            float posx = sprite.getPosition().x+(7+sprite.getLocalBounds().width/2)*xDirection;
            float posy = sprite.getPosition().y-3.1;
            float ang = rand() % 7 + -3 + xOrientation;
            Level::instance(0)->addBullet(new Bullet(posx,posy,ang,200));

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

int Gun::getId()
{
    return id;
}

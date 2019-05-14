#include "Bullet.h"
#include <Level.h>
#include <motorSFML.h>

Bullet::Bullet(double posx, double posy, double ang, double maxLen)
{
    id = 4;

    bulletTexture = new Texture("img/bullet.png");
    bulletSprite = new Sprite(*bulletTexture->getTexture());
    bulletSprite->setOrigin(0,bulletTexture->getTexture()->getSize().y/2);
    bulletSprite->setPosition(posx, posy);
    bulletSprite->setRotation(ang);

    posiniX=posx;
    posiniY=posy;

    angle = ang*M_PI/180;
    maxLength = maxLen;

    float width = bulletSprite->getLocalBounds().width;
    float height = bulletSprite->getLocalBounds().height;

    body = Physics2D::Instance()->createBulletBody(posx, posy, width, height, (ang)*3.14/180.0);
    //body->getBody()->SetBullet(true);
    body->setUserData(this);
}

void Bullet::update()
{
    body->getBody()->SetLinearVelocity(b2Vec2(VEL*cos(angle), VEL*sin(angle)));

    bulletSprite->setPosition(body->getPositionX(), body->getPositionY());
    //bulletSprite.move(VEL*cos(angle), VEL*sin(angle));
    if(sqrt(pow(bulletSprite->getPosition().x-posiniX, 2)+pow(bulletSprite->getPosition().y-posiniY, 2))>=maxLength)
    {
        mustDelete = true;
    }

    if (mustDelete)
        delete this;
}

void Bullet::deleteMe() {
    mustDelete = true;
}

void Bullet::draw(sf::RenderWindow &app)
{
    motorSFML::Instance()->draw(bulletSprite->getSprite()); //app.draw(bulletSprite);
}


Bullet::~Bullet()
{
    //cout << "voy a borrarme" << endl;
    Level* level = Level::instance(0);
        level->removeBullet(this);
    //cout << "borro mi body:" <<endl;
    delete body;
    delete bulletSprite;
    delete bulletTexture;
}

int Bullet::getId()
{
    return id;
}

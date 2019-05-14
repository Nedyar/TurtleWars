#include "WeaponSpawner.h"
#include <Level.h>

WeaponSpawner::WeaponSpawner(int t, double x, double y)
{
    id = 2;
    if (t < 1 || t > 3)
        t = 1;
    type=t;

    platformTexture = new Texture("img/popupPad.png");
    platformSprite = new Sprite(*platformTexture->getTexture());
    platformSprite->setOrigin(platformSprite->getLocalBounds().width/2,platformSprite->getLocalBounds().height);
    platformSprite->setPosition(x, y);

    ballTexture1 = new Texture("img/spawnerBall.png");
    ballSprite1 = new Sprite(*ballTexture1->getTexture());
    ballSprite1->setOrigin(ballSprite1->getLocalBounds().width/2,ballSprite1->getLocalBounds().height/2);
    ballSprite1->setPosition(x-platformTexture->getSize().x/2, y-10);


    ballTexture2 = new Texture("img/spawnerBall.png");
    ballSprite2 = new Sprite(*ballTexture2->getTexture());
    ballSprite2->setOrigin(ballSprite2->getLocalBounds().width/2,ballSprite2->getLocalBounds().height/2);
    ballSprite2->setPosition(x+platformTexture->getSize().x/2, y-10);

    weaponSpawned = nullptr;

    //body = Physics2D::Instance()->createRectangleBody(x,y,platformTexture.getSize().x,platformTexture.getSize().y,2);
    float width = platformSprite->getLocalBounds().width;
    float height = platformSprite->getLocalBounds().height+7+ballSprite2->getLocalBounds().height/2;
    body = Physics2D::Instance()->createSpawnBody(x,y-height/2,width,height);
    body->setUserData(this);

    spawnWeapon();
}

WeaponSpawner::~WeaponSpawner()
{
    //dtor
}

Body* WeaponSpawner::getBody()
{
    return body;
}

void WeaponSpawner::update()
{

    if(clock.getElapsedTime().asSeconds()>=4 && weaponSpawned == nullptr)
    {
        spawnWeapon();
    }

    // Balls Animation
    if(ballSprite1->getPosition().x >= platformSprite->getPosition().x+platformTexture->getSize().x/2)
    {
        ballSprite1->setPosition(ballSprite1->getPosition().x-platformTexture->getSize().x,ballSprite1->getPosition().y);
        ballSprite2->setPosition(ballSprite2->getPosition().x+platformTexture->getSize().x,ballSprite2->getPosition().y);
    }

    ballSprite1->setPosition(ballSprite1->getPosition().x+.1, ballSprite1->getPosition().y);
    ballSprite2->setPosition(ballSprite2->getPosition().x-.1, ballSprite2->getPosition().y);
}

void WeaponSpawner::draw(sf::RenderWindow &app)
{
    motorSFML* motor = motorSFML::Instance();
    motor->draw(platformSprite->getSprite());
    motor->draw(ballSprite1->getSprite());
    if (weaponSpawned != nullptr)
        weaponSpawned->draw(app);
    motor->draw(ballSprite2->getSprite());
}

bool WeaponSpawner::spawnWeapon()
{
    switch (type)
    {
    case 1: // Gun
        weaponSpawned = new Gun(platformSprite->getPosition().x, platformSprite->getPosition().y-10);
        return true;

    case 2: // Grenade
        weaponSpawned = new Grenade(platformSprite->getPosition().x, platformSprite->getPosition().y-10);
        return true;

    case 3: // Shotgun
        weaponSpawned = new ShotGun(platformSprite->getPosition().x, platformSprite->getPosition().y-10);
        return true;
    }
    return false;
}

Weapon* WeaponSpawner::takeWeapon() {
    Weapon* returned = weaponSpawned;
    weaponSpawned = nullptr;

    if(returned != nullptr)
        clock.restart();

    return returned;
}

int WeaponSpawner::getId() {
    return id;
}

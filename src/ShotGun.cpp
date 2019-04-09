#include "ShotGun.h"

ShotGun::ShotGun(double posx, double posy)
{
    shotGunTexture.loadFromFile("img/shotgun.png");
    shotGunSprite.setTexture(shotGunTexture);

    ammo=3;
    shooted = false;

    shotGunSprite.setPosition(posx,posy);
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
        cout << "Recarga" << endl;
        return true;
    }
    else
        return false;
}

std::vector<Bullet*> ShotGun::shoot()
{
    std::vector<Bullet*> bullets;
    if (ammo > 0)
    {
        if (!reload())
        {
            shooted = true;
            ammo--;
            bullets.push_back(new Bullet(shotGunSprite.getPosition().x+shotGunTexture.getSize().x,shotGunSprite.getPosition().y+10,rand() % 6 + 9,100));
            bullets.push_back(new Bullet(shotGunSprite.getPosition().x+shotGunTexture.getSize().x,shotGunSprite.getPosition().y+10,rand() % 6 + 3,100));
            bullets.push_back(new Bullet(shotGunSprite.getPosition().x+shotGunTexture.getSize().x,shotGunSprite.getPosition().y+10,rand() % 6 + (-3),100));
            bullets.push_back(new Bullet(shotGunSprite.getPosition().x+shotGunTexture.getSize().x,shotGunSprite.getPosition().y+10,rand() % 6 + (-9),100));
            bullets.push_back(new Bullet(shotGunSprite.getPosition().x+shotGunTexture.getSize().x,shotGunSprite.getPosition().y+10,rand() % 6 + (-15),100));
            cout << "Pam" << endl;
            return bullets;
        }
    }
    else
    {
        cout << "Sin municion" << endl;
    }
    return bullets;

}

void ShotGun::update()
{

}

void ShotGun::render(sf::RenderWindow &app)
{
    app.draw(shotGunSprite);
}

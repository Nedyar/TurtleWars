#include "ShotGun.h"

ShotGun::ShotGun(double posx, double posy)
{
    shotGunTexture.loadFromFile("img/shotgun.png");
    shotGunSprite.setTexture(shotGunTexture);

    shotGunLoaderTexture.loadFromFile("img/shotgunLoader.png");
    shotGunLoaderSprite.setTexture(shotGunLoaderTexture);
    shotGunLoaderSprite.setTextureRect(sf::IntRect(0,0,8,8));

    ammo=3;
    shooted = false;
    shootAnim = false;
    shootAnimBack = false;

    shotGunSprite.setPosition(posx,posy);
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
        cout << "Recarga" << endl;
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

std::vector<Bullet*> ShotGun::shoot()
{
    std::vector<Bullet*> bullets;
    if (ammo > 0)
    {
        if (!reload()&&!shootAnimBack&&!shootAnim)
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
    if(shootAnim)
    {
        shootAnimation();
    }
}

void ShotGun::render(sf::RenderWindow &app)
{
    app.draw(shotGunSprite);
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

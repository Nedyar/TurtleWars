#include "WeaponSpawner.h"
#include <Level.h>

WeaponSpawner::WeaponSpawner(int t, double x, double y)
{
    type=t;

    platformTexture.loadFromFile("img/popupPad.png");
    platformSprite.setTexture(platformTexture);

    ballTexture1.loadFromFile("img/spawnerBall.png");
    ballSprite1.setTexture(ballTexture1);

    posx = x;
    posy = y;
    setpos();

    created = false;
    animationAux=true;
    animationScale=true;

    weaponSpawned = nullptr;

}

WeaponSpawner::~WeaponSpawner()
{
    //dtor
}

void WeaponSpawner::update()
{

    if(clock.getElapsedTime().asSeconds()>=4 && !created)
    {
        spawnWeapon();
    }

    ballAnimation();
}

void WeaponSpawner::draw(sf::RenderWindow &app)
{
    app.draw(platformSprite);
    if (weaponSpawned != nullptr)
        weaponSpawned->draw(app);
    app.draw(ballSprite1);
    app.draw(ballSprite2);
}

void WeaponSpawner::setpos()
{
    platformSprite.setPosition(posx, posy);
    //platformSprite.setScale(50,50);
    ballSprite1.setPosition(posx, posy-10);
    //ballSprite2.setPosition(x+platformTexture.getSize().x, y-10);
}


bool WeaponSpawner::spawnWeapon()
{

    switch (type)
    {
    case 1: // Gun
    {
        weaponSpawned = new Gun(posx, posy-10);
        created = true;
    }
    break;

    case 2: // Grenade
    {
        weaponSpawned = new Grenade(posx, posy-15);
        created = true;
    }
    break;

    case 3: // Shotgun
    {
        weaponSpawned = new ShotGun(posx-5, posy-25);
        created = true;
    }
    break;
    }
    return created;
}

void WeaponSpawner::ballAnimation()
{
    int a=-1;
    float percentDone = std::min(1.0, clockA.getElapsedTime().asMilliseconds()/3000.0);

    if(ballSprite1.getPosition().x>=platformSprite.getPosition().x+platformTexture.getSize().x)
    {
        animationAux=false;
        clockA.restart();
    }

    if(ballSprite1.getPosition().x<=platformSprite.getPosition().x-ballTexture1.getSize().x)
        animationAux=true;

    if(animationAux)
        a=1;

    ballSprite1.setPosition(ballSprite1.getPosition().x+platformTexture.getSize().x*0.01*a, ballSprite1.getPosition().y);

    /* cout << clockA.getElapsedTime().asMilliseconds() << endl;

     if(ballSprite1.getPosition().x==(platformSprite.getPosition().x+platformTexture.getSize().x)/2)
     {
         if(animationScale)
             animationScale=false;
         else
             animationScale=true;
     }

     if(animationAux && animationScale){

     }
     else if(animationAux && !animationScale){
     }
     else if(!animationAux && !animationScale){
     }
     else if(!animationAux && animationScale){
     }

     double sizex=0.0;

     sizex=percentDone*4;

     ballSprite1.setScale(sizex, sizex);

    */
}

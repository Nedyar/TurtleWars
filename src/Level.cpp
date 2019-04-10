#include "Level.h"
#include <SFML/Graphics.hpp>

Level* Level::pinstance = 0;

Level::Level(int nPlayers)
{
    groundTexture.loadFromFile("img/ground.png");
    groundSprite = sf::Sprite(groundTexture);
    groundSprite.setOrigin(groundSprite.getLocalBounds().width/2,groundSprite.getLocalBounds().height/2);
    groundSprite.setPosition(groundSprite.getLocalBounds().width/2,600-groundSprite.getLocalBounds().height/2);
    groundBody = Physics2D::Instance()->createRectangleBody(groundSprite.getPosition().x,groundSprite.getPosition().y,groundSprite.getGlobalBounds().width,groundSprite.getGlobalBounds().height,0);

    players = new Character*[nPlayers];
    for (int i = 0; i < nPlayers; i++)
    {
        Character* player = new Character(i+1);
        players[i] = player;
    }

    weaponSpawners = new WeaponSpawner*[3];

    for (int i = 0; i < 3; i++)
    {
        weaponSpawners[i] = new WeaponSpawner(i%3+1,32*(i+2),600-groundSprite.getLocalBounds().height);
    }
}

Level::~Level()
{
    //dtor
}

Level* Level::instance(int nPlayers = 1)
{
    if (pinstance == 0)
        pinstance = new Level(nPlayers);
    return pinstance;
}

void Level::handleEvents()
{

    // TODO: Making the event handler control the current number of players
    Character* player = players[0];


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        player->walk(true);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        player->walk(false);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        player->jump();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        player->crouch();
    else
        player->standUp();



    /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) startGunShoot = true;
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) finishGunShoot = true;

    if(startGunShoot && finishGunShoot)
    {

        bulletAux=weapons[0]->shoot();

        if(!bulletAux.empty()){

            for(int i=0; i<bulletAux.size(); i++){

                bullets.push_back(bulletAux.at(i));
            }
        }
        bulletAux.clear();
        finishGunShoot = false;
    }*/



    /*
    Character* player2 = players[1];

    if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 10)
        player2->walk(true);
    else if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -10)
        player2->walk(false);

    if(sf::Joystick::isButtonPressed(0, 0))
        player2->jump();
    if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 30)
        player2->crouch();
    else
        player2->standUp();*/

    //std::cout << sf::Joystick::isButtonPressed(0, 0) << std::endl; // A
    //std::cout << sf::Joystick::isButtonPressed(0, 1) << std::endl; // B
    //std::cout << sf::Joystick::isButtonPressed(0, 2) << std::endl; // X
    //std::cout << sf::Joystick::isButtonPressed(0, 3) << std::endl; // Y

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        player->dropWeapon();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        player->shoot();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        player->fakeDie();
    }

}

void Level::update()
{
    for (int i = 0; i < 1; i++)
    {
        Character* player = players[i];
        player->update();
    }

    for (int i = 0; i < 3; i++)
    {
        weaponSpawners[i]->update();
    }

    for (int i = 0; i < weapons.size(); i++)
    {
        weapons.at(i)->update();
    }

    for(int i=0; i<bullets.size(); i++)
    {
        bullets.at(i)->update();

        // Esta comprobacion debe hacerse en el update de la clase bullet
        if(sqrt(pow(bullets.at(i)->bulletSprite.getPosition().x-bullets.at(i)->posiniX, 2)+pow(bullets.at(i)->bulletSprite.getPosition().y-bullets.at(i)->posiniY, 2))>=bullets.at(i)->maxLength)
        {
            delete bullets[i];
            bullets.erase(bullets.begin()+i);
        }
    }

    Physics2D::Instance()->updateWorld();
}

void Level::draw(sf::RenderWindow &app)
{
    for (int i = 0; i < 3; i++)
    {
        weaponSpawners[i]->draw(app);
        app.draw(weaponSpawners[i]->getBody()->dameRect());
    }

    for (int i = 0; i < weapons.size(); i++)
    {
        weapons.at(i)->draw(app);
    }

    for (int i = 0; i < bullets.size(); i++)
    {
        bullets.at(i)->draw(app);
    }

    for (int i = 0; i < 1; i++)
    {
        Character* player = players[i];
        player->draw(app);
        app.draw(player->getBody()->dameRect());
    }

    app.draw(groundSprite);
    app.draw(groundBody->dameRect());
}

void Level::addWeapon(Weapon* weapon)
{
    weapons.push_back(weapon);
}

void Level::addBullet(Bullet* bullet)
{
    bullets.push_back(bullet);
}

void Level::removeWeapon(Weapon* weapon)
{
    for (int i = 0; i < weapons.size(); i++)
    {
        if (weapons.at(i) == weapon)
        {
            weapons.erase(weapons.begin()+i);
            break;
        }
    }
}

void Level::removeBullet(Bullet* bullet)
{
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets.at(i) == bullet)
        {
            bullets.erase(bullets.begin()+i);
            break;
        }
    }
}

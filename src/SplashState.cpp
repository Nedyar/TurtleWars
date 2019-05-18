#include "SplashState.h"
#include <Game.h>
#include <Level.h>
#include <motorSFML.h>

SplashState::SplashState()
{
    font.loadFromFile("fonts/majorforce.ttf");

    presskey.setFont(font);
    presskey.setString("Press Start");
    presskey.setCharacterSize(40);
    presskey.setColor(sf::Color::White);
    presskey.setOrigin(634/2,41/2);
    presskey.setPosition(960/2,600);
    sf::FloatRect textRect1 = presskey.getLocalBounds();
    presskey.setOrigin(textRect1.left + textRect1.width/2.0f, textRect1.top  + textRect1.height/2.0f);
    presskey.setPosition(960/2,570);
}

SplashState::~SplashState()
{
    //dtor
}

void SplashState::handleEvents()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    if(this->clock.getElapsedTime().asSeconds()>5)
        loadLevel();
}

void SplashState::loadLevel() {
    Game::instance()->popState();
    Game::instance()->pushState(Level::instance());
}

void SplashState::update()
{

    if(this->clock.getElapsedTime().asSeconds()>SPLASH_TIME){
        loadLevel();
    }


}

void SplashState::draw()
{
    motorSFML::Instance()->resetCamara();
    Texture tittle("img/tittle.png");
    Sprite* sprite = new Sprite(*tittle.getTexture());

    sprite->setOrigin(635/2,345/2);
    sprite->setPosition(960/2,250);

    Texture load("img/load.png");
    Sprite* sprites = new Sprite(*load.getTexture());

    sprites->setOrigin(44/2,38/2);

/*sf::Text tittle;
    tittle.setFont(font);

    if(num==0)
    {
        tittle.setString("Pause");
    }
    else
    {
        tittle.setString("Turtle Royal");
    }


    tittle.setCharacterSize(120);
    tittle.setColor(sf::Color::White);

    sf::FloatRect textRect1 = tittle.getLocalBounds();
    tittle.setOrigin(textRect1.left + textRect1.width/2.0f, textRect1.top  + textRect1.height/2.0f);

    tittle.setPosition(960/2,125);*/

    //Texture press("img/presskey.png");
    //Sprite* presskey = new Sprite(*press.getTexture());


    int x = 234;
    float reloj = 0.5;

    motorSFML::Instance()->draw(sprite->getSprite());
    for(int i = 0 ; i < 8 ; i++)
    {
        if(this->clock.getElapsedTime().asSeconds()>reloj)
        {
            sprites->setPosition(x,500);
            motorSFML::Instance()->draw(sprites->getSprite());
            x+=64;
            reloj += 0.6;
        }
    }
    if(this->clock.getElapsedTime().asSeconds()>5&&(int)this->clock.getElapsedTime().asSeconds()%2==0)
    {
        presskey.setColor(sf::Color::Transparent);

    }else
        presskey.setColor(sf::Color::White);
    if(this->clock.getElapsedTime().asSeconds()>5)
        motorSFML::Instance()->draw(presskey);
}

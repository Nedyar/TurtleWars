#include "IntroState.h"

#include "Texture.h"
#include "Sprite.h"
#include "motorSFML.h"
#include "Game.h"

IntroState::IntroState()
{
    motorSFML::Instance()->setMusic("./sounds/title.wav",50);
}

IntroState::~IntroState()
{
    //dtor
}

void IntroState::handleEvents()
{
}
void IntroState::update()
{
    if(this->clock.getElapsedTime().asSeconds()>INTRO_TIME) {
        Game::instance()->popState();
        Game::instance()->pushState(new MainMenu());
    }
}

void IntroState::draw()
{
    motorSFML::Instance()->resetCamara();
    Texture logo("img/logo.png");
    Texture presents("img/presents.png");
    Texture tittle("img/turtleroyal.png");

    Sprite* spritelogo = new Sprite(*logo.getTexture());
    Sprite* spritepresents = new Sprite(*presents.getTexture());
    Sprite* spritetittle = new Sprite(*tittle.getTexture());

    spritelogo->setOrigin(0,0);
    spritelogo->setPosition(355,70);

    spritepresents->setOrigin(0,0);
    spritepresents->setPosition(266,380);

    spritetittle->setOrigin(0,0);
    spritetittle->setPosition(130,480);


    motorSFML::Instance()->draw(spritelogo->getSprite());

    if(this->clock.getElapsedTime().asSeconds()>2)
        motorSFML::Instance()->draw(spritepresents->getSprite());

    if(this->clock.getElapsedTime().asSeconds()>4)
        motorSFML::Instance()->draw(spritetittle->getSprite());
}

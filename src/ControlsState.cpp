#include "ControlsState.h"

#include <motorSFML.h>
#include <Game.h>

ControlsState::ControlsState()
{
    texture = new Texture("img/Controls.png");
    sprite = new Sprite(*texture->getTexture());

    sprite->setTextureRect(0,0,texture->getSize().x,texture->getSize().y);
    sprite->setOrigin(sprite->getLocalBounds().width/2,sprite->getLocalBounds().height/2);
    sprite->setPosition(960/2, 640/2);

    font.loadFromFile("fonts/majorforce.ttf");

    controls.setFont(font);
    controls.setString("JoyStick");
    controls.setCharacterSize(40);
    controls.setColor(sf::Color::White);
    sf::FloatRect textRect1 = controls.getLocalBounds();
    controls.setOrigin(textRect1.left + textRect1.width/2.0f, textRect1.top  + textRect1.height/2.0f);
    controls.setPosition(240,40);

    controlsKeyboard.setFont(font);
    controlsKeyboard.setString("KeyBoard");
    controlsKeyboard.setCharacterSize(40);
    controlsKeyboard.setColor(sf::Color::Black);
    sf::FloatRect textRect2 = controlsKeyboard.getLocalBounds();
    controlsKeyboard.setOrigin(textRect2.left + textRect2.width/2.0f, textRect2.top  + textRect2.height/2.0f);
    controlsKeyboard.setPosition(720,40);

}

ControlsState::~ControlsState()
{
    //dtor
}

void ControlsState::handleEvents()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        action = 1;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        action = 2;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        action = 3;
}

void ControlsState::update()
{
    if (action == 1)
    {
        texture = new Texture("img/Controls.png");
        sprite = new Sprite(*texture->getTexture());

        controls.setColor(sf::Color::White);
        controlsKeyboard.setColor(sf::Color::Black);

        sprite->setTextureRect(0,0,texture->getSize().x,texture->getSize().y);
        sprite->setOrigin(sprite->getLocalBounds().width/2,sprite->getLocalBounds().height/2);
        sprite->setPosition(960/2, 640/2);
    }
    else if (action == 2)
    {
        texture = new Texture("img/ControlsKeyboard.png");
        sprite = new Sprite(*texture->getTexture());

        controls.setColor(sf::Color::Black);
        controlsKeyboard.setColor(sf::Color::White);

        sprite->setTextureRect(0,0,texture->getSize().x,texture->getSize().y);
        sprite->setOrigin(sprite->getLocalBounds().width/2,sprite->getLocalBounds().height/2);
        sprite->setPosition(960/2, 640/2);
    }
    else if (action == 3)
    {
        Game::instance()->popState();
    }
    action = 0;
}

void ControlsState::draw()
{
    motorSFML* motor = motorSFML::Instance();

    motor->draw(sprite->getSprite());
    motor->draw(controls);
    motor->draw(controlsKeyboard);
}

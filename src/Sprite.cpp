#include "Sprite.h"

Sprite::Sprite(sf::Texture &tex)
{
    sprite = new sf::Sprite(tex);
    swapState = false;
}

Sprite::~Sprite()
{
    delete sprite;
}

void Sprite::setTextureRect(int x, int y, int width, int height)
{
    sprite->setTextureRect(sf::IntRect(x, y, width, height));
}

void Sprite::setPosition(double x, double y)
{
    sprite->setPosition(x,y);
}

void Sprite::setOrigin(double x, double y)
{
    sprite->setOrigin(x,y);
}


void Sprite::setScale(double x, double y)
{
    sprite->setScale(x,y);
}

void Sprite::setRotation(double ang)
{
    sprite->setRotation(ang);
}

void Sprite::Swap()
{
    swapState = !swapState;
    sprite->setScale(-1, 1);
}

bool Sprite::isSwap()
{
    return swapState;
}

sf::Sprite *Sprite::getSprite()
{
    return sprite;
}

sf::FloatRect Sprite::getLocalBounds()
{
    return sprite->getLocalBounds();
}

const sf::Vector2f& Sprite::getPosition()
{
    sprite->getPosition();
}



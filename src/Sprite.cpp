#include "Sprite.h"

Sprite::Sprite(sf::Texture &tex)
{
    sprite = new sf::Sprite(tex);
    swapState = false;
}

Sprite::~Sprite()
{
    //dtor
}

void Sprite::setTextureRect(int x, int y, int width, int height)
{
    sprite->setTextureRect(sf::IntRect(x, y, width, height));
}

void Sprite::setPosition(int x, int y)
{
    sprite->setPosition(x,y);
}

void Sprite::setOrigin(int x, int y)
{
    sprite->setOrigin(x,y);
}

void Sprite::setScale(int x, int y)
{
    sprite->setScale(x,y);
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



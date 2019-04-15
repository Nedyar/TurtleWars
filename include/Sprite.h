#ifndef SPRITE_H
#define SPRITE_H

#include "motorSFML.h"

class Sprite
{
    public:
        Sprite(sf::Texture &tex);
        ~Sprite();
        void setTextureRect(int x, int y, int width, int height);
        void setPosition(double x, double y);
        void setOrigin(double x, double y);
        void setScale(double x, double y);
        void setRotation(double ang);
        void Swap();
        bool isSwap();
        sf::Sprite *getSprite();
        sf::FloatRect getLocalBounds();
        const sf::Vector2f& getPosition();

    protected:

    private:
        sf::Sprite *sprite;
        bool swapState;
};

#endif // SPRITE_H

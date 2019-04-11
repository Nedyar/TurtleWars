#ifndef SPRITE_H
#define SPRITE_H

#include "motorSFML.h"

class Sprite
{
    public:
        Sprite(sf::Texture &tex);
        ~Sprite();
        void setTextureRect(int x, int y, int width, int height);
        void setPosition(int x, int y);
        void setOrigin(int x, int y);
        void setScale(int x, int y);
        sf::Sprite *getSprite();

    protected:

    private:
        sf::Sprite *sprite;
};

#endif // SPRITE_H

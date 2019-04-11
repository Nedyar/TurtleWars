#ifndef TEXTURE_H
#define TEXTURE_H

#include "motorSFML.h"


class Texture
{
    public:
        Texture(const char* rutaTex);
        ~Texture();
        sf::Texture *getTexture();

    protected:

    private:
        sf::Texture *tex;
};

#endif // TEXTURE_H

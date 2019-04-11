#include "Texture.h"

Texture::Texture(const char* rutaTex)
{
    tex = new sf::Texture();
    if (!tex->loadFromFile(rutaTex)){exit(0);}
}

Texture::~Texture()
{
    //dtor
}

sf::Texture* Texture::getTexture()
{
    return tex;
}

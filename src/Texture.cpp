#include "Texture.h"

Texture::Texture(const char* rutaTex)
{
    tex = new sf::Texture();
    if (!tex->loadFromFile(rutaTex)){exit(0);}
}

Texture::~Texture()
{
    delete tex;
}

sf::Texture* Texture::getTexture() {
    return tex;
}

sf::Vector2u Texture::getSize()
{
    return tex->getSize();
}

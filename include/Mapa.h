#ifndef MAPA_H
#define MAPA_H

#include "../xml/tinyxml.h"
#include "Texture.h"
#include <SFML/Graphics.hpp>
#include "Sprite.h"
#include <iostream>
#include <Physics2D.h>
#include <Body.h>


class Mapa
{
    public:
        Mapa(TiXmlElement* map);
        ~Mapa();
        void setGidMatrix(TiXmlElement* map);
        void setSpriteMatrix();
        void setBodyMap(TiXmlElement* objLayer);
        void drawSpriteMatrix(sf::RenderWindow &window);
        void drawBodyMap(sf::RenderWindow &window);
        int getRows();
        int getCols();
        int **getmGid();
        Sprite ***getmTilemapSprite();


    protected:

    private:
        int cols;
        int rows;
        int tileWidth;
        int tileHeight;
        const char* source;
        int **mGid;
        Sprite ***mTilemapSprite;
        Body** bodyMap;
};

#endif // MAPA_H

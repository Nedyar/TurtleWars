#ifndef MAPA_H
#define MAPA_H

#include "../xml/tinyxml.h"
#include "motorSFML.h"
#include <SFML/Graphics.hpp>
#include <iostream>


class Mapa
{
    public:
        Mapa(TiXmlElement* map);
        ~Mapa();
        void setGidMatrix(TiXmlElement* map);
        void setSpriteMatrix();
        void drawSpriteMatrix(sf::RenderWindow &window);
        int getRows();
        int getCols();
        int **getmGid();
        sf::Sprite ***getmTilemapSprite();


    protected:
    private:

        int cols;
        int rows;
        int tileWidth;
        int tileHeight;
        const char* source;
        int **mGid;
        sf::Sprite ***mTilemapSprite;
};

#endif // MAPA_H

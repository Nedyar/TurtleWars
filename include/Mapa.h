#ifndef MAPA_H
#define MAPA_H

#include "../xml/tinyxml.h"
#include "Texture.h"
#include <SFML/Graphics.hpp>
#include "Sprite.h"
#include <Physics2D.h>
#include <Body.h>


class Mapa
{
    public:
        Mapa(TiXmlElement* Map);
        ~Mapa();
        void setGidMatrix(TiXmlElement* Map);
        void setSpriteMatrix();
        void setBodyMap(TiXmlElement* objLayer);
        void drawSpriteMatrix();
        void drawBodyMap();
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
        Texture* tex;
        int **mGid;
        Sprite ***mTilemapSprite;
        Body** bodyMap;
};

#endif // MAPA_H

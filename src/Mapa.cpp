#include "Mapa.h"

Mapa::Mapa(TiXmlElement* map)
{

/*  CARGAR LOS PARAMETROS PARA LA MATRIX Y SPRITES  */
    map->QueryIntAttribute("width", &cols);
    map->QueryIntAttribute("height", &rows);
	map->QueryIntAttribute("tilewidth", &tileWidth);
	map->QueryIntAttribute("tileheight", &tileHeight);
    source = map->FirstChildElement("tileset")->Attribute("source");

    mGid = new int*[rows];
    for(int i=0; i<rows; ++i)
        mGid[i] = new int[cols];


    mTilemapSprite = new sf::Sprite**[rows];
    for(int i=0; i<rows; ++i)
        mTilemapSprite[i] = new sf::Sprite*[cols];

}

Mapa::~Mapa()
{
    //dtor
}


void Mapa::setGidMatrix(TiXmlElement* map)
{

    TiXmlElement* tile = map->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    int posY = 0, posX = 0, contador = 0, valor = 0;

    do
    {
        posY = contador/cols;
        posX = contador - (posY * cols);
        if( tile->QueryIntAttribute("gid", &valor) == TIXML_NO_ATTRIBUTE)
            valor = 0;

        mGid[posY][posX] = valor;
        ++contador;
        tile = tile->NextSiblingElement("tile");

    }while(tile);

}

void Mapa::setSpriteMatrix()
{

    sf::Texture *tex = new sf::Texture();
    std::cout << source << std::endl;
    if (!tex->loadFromFile(source)){exit(0);}
    std::cout << "juju" << std::endl;


    for(int i=0; i<rows; ++i)
    {
        for(int j=0; j<cols; ++j)
        {
            int gid = mGid[i][j] - 1;
            if(gid < 1)
                gid = 1;
            int row = gid/tileWidth;
            int col = gid - (row * tileHeight);

            if(gid > 0)
            {
                mTilemapSprite[i][j] = new sf::Sprite(*tex);
                mTilemapSprite[i][j]->setTextureRect(sf::IntRect(col*tileWidth, row*tileHeight, tileWidth, tileHeight));
                mTilemapSprite[i][j]->setPosition(j*32, i*32);
            }
            else
                mTilemapSprite[i][j] = NULL;
        }
    }

}

void Mapa::drawSpriteMatrix(sf::RenderWindow &window)
{
    motorSFML* motor = motorSFML::Instance();

    for(int i=0; i<rows; ++i)
    {
        for(int j=0; j<cols; ++j)
        {
            if(mTilemapSprite[i][j] != NULL)
                motor->draw(window, mTilemapSprite[i][j]);
                //window.draw( *mTilemapSprite[i][j] );
        }
    }
}

/** GETERS **/

int Mapa::getCols()
{
    return cols;
}

int Mapa::getRows()
{
    return rows;
}

int **Mapa::getmGid()
{
    return mGid;
}

sf::Sprite ***Mapa::getmTilemapSprite()
{
    return mTilemapSprite;
}

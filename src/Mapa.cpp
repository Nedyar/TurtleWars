#include "Mapa.h"

Mapa::Mapa(TiXmlElement* Map)
{
/*  CARGAR LOS PARAMETROS PARA LA MATRIX Y SPRITES  */
    Map->QueryIntAttribute("width", &cols);
    Map->QueryIntAttribute("height", &rows);
	Map->QueryIntAttribute("tilewidth", &tileWidth);
	Map->QueryIntAttribute("tileheight", &tileHeight);

    tex = new Texture(Map->FirstChildElement("tileset")->Attribute("source"));

    mGid = new int*[rows];
    for(int i=0; i<rows; ++i)
        mGid[i] = new int[cols];


    mTilemapSprite = new Sprite**[rows];
    for(int i=0; i<rows; ++i)
        mTilemapSprite[i] = new Sprite*[cols];


    TiXmlElement* obj = Map->FirstChildElement("objectgroup")->FirstChildElement("object");
    int conta = 0;
    do
    {
        conta++;
        obj = obj->NextSiblingElement("object");
    }while(obj);
    //cout << conta << endl;
    bodyMap = new Body*[conta];

}

Mapa::~Mapa()
{
    //dtor
}

void Mapa::setGidMatrix(TiXmlElement* Map)
{
    TiXmlElement* tile = Map->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    int posY = 0, posX = 0, contador = 0, valor = 0;

    do
    {
        posY = contador/cols;
        posX = contador - (posY * cols);
        if( tile->QueryIntAttribute("gid", &valor) == TIXML_NO_ATTRIBUTE)
            valor = -1;

        mGid[posY][posX] = valor;
        ++contador;
        tile = tile->NextSiblingElement("tile");

    }while(tile);

}

void Mapa::setBodyMap(TiXmlElement* objLayer)
{

    TiXmlElement* obj = objLayer->FirstChildElement("object");
    float posY = 0.0, posX = 0.0, height = 0.0, width = 0.0;
    int conta = 0;

    do
    {

        obj->QueryFloatAttribute("x", &posX);
        obj->QueryFloatAttribute("y", &posY);
        obj->QueryFloatAttribute("width", &width);
        obj->QueryFloatAttribute("height", &height);

        bodyMap[conta] = Physics2D::Instance()->createRectangleBody(posX+width/2, posY+height/2, width, height, 0);
        conta++;
        obj = obj->NextSiblingElement("object");
    }while(obj);


}

void Mapa::setSpriteMatrix()
{

    for(int i=0; i<rows; ++i)
    {
        for(int j=0; j<cols; ++j)
        {
            int gid = mGid[i][j] - 1;
            int row = gid/4;
            int col = gid - (row * 4);

            if(gid > -1)
            {
                mTilemapSprite[i][j] = new Sprite(*tex->getTexture());
                mTilemapSprite[i][j]->setTextureRect(col*tileWidth, row*tileHeight, tileWidth, tileHeight);
                mTilemapSprite[i][j]->setPosition(j*32, i*32);
            }
            else
                mTilemapSprite[i][j] = NULL;
        }
    }

}

void Mapa::drawSpriteMatrix()
{
    motorSFML* motor = motorSFML::Instance();

    for(int i=0; i<rows; ++i)
    {
        for(int j=0; j<cols; ++j)
        {
            if(mTilemapSprite[i][j] != NULL)
                motor->draw(mTilemapSprite[i][j]->getSprite());
                //window.draw( *mTilemapSprite[i][j] );
        }
    }
}

void Mapa::drawBodyMap()
{
    //motorSFML* motor = motorSFML::Instance();

    for(int i=0; i<7; ++i)
    {
                //motor->draw(window, bodyMap[i]->dameRect());
                bodyMap[i]->pintaRect();
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

Sprite ***Mapa::getmTilemapSprite()
{
    return mTilemapSprite;
}

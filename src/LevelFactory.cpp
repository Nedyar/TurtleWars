#include "LevelFactory.h"

LevelFactory* LevelFactory::pInstance = 0;

LevelFactory::LevelFactory()
{
    doc = TiXmlDocument("./mapa/levelFactory.xml");
    doc.LoadFile();
}

LevelFactory::~LevelFactory()
{
    //dtor
}

LevelFactory* LevelFactory::Instance()
{
    if(pInstance == 0)
        pInstance = new LevelFactory();

    return pInstance;
}

/**----------------------------------------*/


Mapa* LevelFactory::mapLoader(int seleccion)
{
    TiXmlElement* level = doc.FirstChildElement("level");
    TiXmlElement* mapElement = NULL;
    TiXmlDocument* docMap = NULL;

    do
    {
        if(level->FirstAttribute()->IntValue() == seleccion)
        {
            const char* nameMap = level->FirstChildElement("mapa")->Attribute("maptmx");
            docMap = new TiXmlDocument(nameMap);
            docMap->LoadFile();

            mapElement = docMap->FirstChildElement("map");
            break;
        }
        level = level->NextSiblingElement("level");


    }while(level);

    /**  CREAMOS EL OBJ MAPA Y METEMOS LOS GIDs  **/
    Mapa* miMapa = new Mapa(mapElement);
    miMapa->setGidMatrix(mapElement);

    /**  AHORA CREMAOS LOS SPRITES **/
    miMapa->setSpriteMatrix();

    /**  AHORA LOS BODYMAPS  **/
    miMapa->setBodyMap(mapElement->FirstChildElement("objectgroup"));

    return miMapa;

}

Character** LevelFactory::characterLoader(int seleccion, int nPlayers)
{
    TiXmlElement* level = doc.FirstChildElement("level");
    TiXmlElement* characterElement = NULL;
    TiXmlDocument* docMap = NULL;
    Character** players = new Character*[nPlayers];
    float posX = 0.0, posY = 0.0;

    do
    {
        if(level->FirstAttribute()->IntValue() == seleccion)
        {
            const char* nameMap = level->FirstChildElement("mapa")->Attribute("maptmx");
            docMap = new TiXmlDocument(nameMap);
            docMap->LoadFile();
            characterElement = docMap->FirstChildElement("map")->FirstChildElement("objectgroup")->NextSiblingElement("objectgroup")->FirstChildElement("object");
            break;
        }
        level = level->NextSiblingElement("level");

    }while(level);

    for(int i=0; i<nPlayers; i++)
    {
        characterElement->QueryFloatAttribute("x", &posX);
        characterElement->QueryFloatAttribute("y", &posY);
        players[i] = new Character(i+1, posX, posY);
        std::cout << posX << " - " << posY << endl;

        characterElement = characterElement->NextSiblingElement("object");
    }

    return players;
}

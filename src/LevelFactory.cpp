#include "LevelFactory.h"

LevelFactory* LevelFactory::pInstance = 0;

LevelFactory::LevelFactory()
{
    doc = TiXmlDocument("./mapa/levelFactory.xml");
    doc.LoadFile();
}

LevelFactory::~LevelFactory()
{
    delete pInstance;
}

LevelFactory* LevelFactory::Instance()
{
    if(pInstance == 0) {
        pInstance = new LevelFactory();
    }
    return pInstance;
}


Mapa* LevelFactory::mapLoader(int seleccion)
{
    TiXmlElement* level = doc.FirstChildElement("level");
    TiXmlElement* mapElement = nullptr;
    TiXmlDocument* docMap = nullptr;

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

        players[i] = (Character*)malloc(sizeof(Character));
        players[i] = new Character(i+1, posX, posY);

        characterElement = characterElement->NextSiblingElement("object");
    }

    return players;
}

WeaponSpawner** LevelFactory::spawnerLoader(int seleccion)
{
    TiXmlElement* level = doc.FirstChildElement("level");
    TiXmlElement* spawerElement = NULL;
    TiXmlDocument* docMap = NULL;
    WeaponSpawner** spawners = NULL;
    float posX = 0.0, posY = 0.0;

    do
    {
        if(level->FirstAttribute()->IntValue() == seleccion)
        {
            const char* nameMap = level->FirstChildElement("mapa")->Attribute("maptmx");
            docMap = new TiXmlDocument(nameMap);
            docMap->LoadFile();
            spawerElement = docMap->FirstChildElement("map")->FirstChildElement("objectgroup")->NextSiblingElement("objectgroup")->NextSiblingElement("objectgroup");
            spawerElement->QueryIntAttribute("size", &sizeSpawner);
            spawerElement = spawerElement->FirstChildElement("object");
            break;
        }
        level = level->NextSiblingElement("level");

    }while(level);

    spawners = new WeaponSpawner*[sizeSpawner];

    for(int i=0; i<sizeSpawner; i++)
    {
        spawerElement->QueryFloatAttribute("x", &posX);
        spawerElement->QueryFloatAttribute("y", &posY);
        spawners[i] = (WeaponSpawner*)malloc(sizeof(WeaponSpawner));
        spawners[i] = new WeaponSpawner(i%3+1, posX, posY);

        spawerElement = spawerElement->NextSiblingElement("object");
    }

    return spawners;
}

int LevelFactory::getSizeSpawner()
{
    return sizeSpawner;
}

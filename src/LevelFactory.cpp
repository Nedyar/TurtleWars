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
        pInstance = (LevelFactory*)malloc(sizeof(LevelFactory));
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
    Mapa* miMapa = (Mapa*)malloc(sizeof(Mapa));
    miMapa = new Mapa(mapElement);
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

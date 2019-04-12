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

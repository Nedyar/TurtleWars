#ifndef LEVELFACTORY_H
#define LEVELFACTORY_H

#include "Mapa.h"
#include "../xml/tinyxml.h"
#include <iostream>


class LevelFactory
{
    public:
        LevelFactory(const char* ruta);
        ~LevelFactory();
        static LevelFactory* Instance();
        Mapa* mapLoader(int seleccion);

    protected:
        LevelFactory();
        LevelFactory(const LevelFactory&);
        LevelFactory &operator= (const LevelFactory&);

    private:
        static LevelFactory* pInstance;
        TiXmlDocument doc;

};

#endif // LEVELFACTORY_H

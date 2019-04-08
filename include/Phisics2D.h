#ifndef PHISICS2D_H
#define PHISICS2D_H

#include <iostream>

//#include <World.h>
#include <Body.h>
#include <SFML/Graphics.hpp> // cuando me coma la polla esto se borra



class Phisics2D
{
    public:
        static Phisics2D* Instance();
        void createBody(sf::Sprite&); // ahora mismo recibe un sf::sprite, pero luego me come la polla
        //~Phisics2D();
    protected:
        Phisics2D();
        Phisics2D(const Phisics2D & );
        Phisics2D &operator= (const Phisics2D & );

    private:
        Body * bod = nullptr;
        static Phisics2D* instance;
};

#endif // PHISICS2D_H

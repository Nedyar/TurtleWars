#ifndef PHYSICS2D_H
#define PHYSICS2D_H

#include <iostream>

#include <Body.h>
#include <SFML/Graphics.hpp> // cuando me coma la polla esto se borra



class Physics2D
{
    public:
        static Physics2D* Instance();
        Body* createRectangleBody(float positionX, float positionY, float width, float height, int pType = 1);
        void updateWorld();

        //~Physics2D();
    protected:
        Physics2D();
        Physics2D(const Physics2D & );
        Physics2D &operator= (const Physics2D &);

    private:
        static Physics2D* instance;

};

#endif // PHYSICS2D_H

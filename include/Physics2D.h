#ifndef PHYSICS2D_H
#define PHYSICS2D_H

#include <iostream>

//#include <World.h>
#include <Body.h>
#include <SFML/Graphics.hpp> // cuando me coma la polla esto se borra



class Physics2D
{
    public:
        static Physics2D* Instance();
        Body* createCircleBody(sf::Sprite&,float pSize = 8.f, int pType = 1); // ahora mismo recibe un sf::sprite, pero luego me come la polla
        Body* createRectangleBody(sf::Sprite&,float pSize = 8.f, int pType = 1);
        //~Physics2D();
    protected:
        Physics2D();
        Physics2D(const Physics2D & );
        Physics2D &operator= (const Physics2D &);

    private:
        Body * body = nullptr;
        static Physics2D* instance;

        b2BodyType type;
        b2CircleShape shape;
        b2Vec2  spawn;

};

#endif // PHYSICS2D_H

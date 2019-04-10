#ifndef BODY_H
#define BODY_H

//#include "Phisics2D.h"
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <World.h>
#include <iostream>


class Body
{
    public:
        Body(b2BodyType type,b2Vec2 spawn, b2CircleShape shape);
        Body(b2BodyType type,b2Vec2 spawn, b2PolygonShape shape);
        ~Body();

        //FUNCTIONS
        b2Body* getBody();//will deprecate
        void setDensity(float density);
        void setFriction(float friction);
        void setRestitution(float restitution);
        float getPositionX();
        float getPositionY();

        void drawCollider();//Will deprecated


        b2PolygonShape collideShape;
        sf::RectangleShape dameRect();


    protected:

    private:
         //VARIABLES
        World *world = World::Instance();
        b2Body * bod = nullptr;
        b2Fixture * fix = nullptr;

};

#endif // BODY_H

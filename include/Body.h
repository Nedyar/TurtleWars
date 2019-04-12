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
        Body(b2BodyType type,b2Vec2 spawn, b2PolygonShape shape, float density = 1.f, float friction = 0.1f, float restitution = 0.f, int group = 1 , bool avoidRotate = false);
        ~Body();

        //FUNCTIONS
        b2Body* getBody();//will deprecate
        void setDensity(float density);

        b2Body* setFriction(b2Body* body, float friction);

        void setRestitution(float restitution);
        float getPositionX();
        float getPositionY();
        float getAngle();
        void avoidRotate(); // esto creo que no funcionaria

        void drawCollider();//Will deprecated


        b2PolygonShape collideShape;
        sf::RectangleShape dameRect();


    protected:

    private:
        float rad2deg(float rad);
         //VARIABLES
        World *world = World::Instance();
        b2Body * bod = nullptr;
        b2Fixture * fix = nullptr;

};

#endif // BODY_H

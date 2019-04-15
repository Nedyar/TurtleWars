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
        Body(b2BodyType type,b2Vec2 spawn, b2PolygonShape shape, float density, float friction, float restitutio, int group, bool sensor, bool avoidRotate);
        Body(b2BodyType type,b2Vec2 spawn, b2PolygonShape shape, float density, float friction,float restitution, int group, bool avoidRotate);
        Body(b2BodyType type,b2Vec2 spawn, b2CircleShape shape, float density, float friction,float restitution, int group, bool sensor,  bool avoidRotate);
        ~Body();

        //FUNCTIONS
        b2Body* getBody();//will deprecate
        void setDensity(float density);

        b2Body* setFriction(b2Body* body, float friction);

        void setRestitution(float restitution);
        float getPositionX();
        void setUserData(void* userData);

        float getPositionY();
        float getAngle();


        void drawCollider();//Will deprecated


        b2PolygonShape collideShape;

        void pintaRect(sf::RenderWindow &app);


    protected:

    private:
        float rad2deg(float rad);
         //VARIABLES
        b2Body * bod = nullptr;
        b2Fixture * fix = nullptr;

};

#endif // BODY_H

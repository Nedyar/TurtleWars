#ifndef BODY_H
#define BODY_H

//#include "Phisics2D.h"
#include <Box2D/Box2D.h>
#include <World.h>
#include <iostream>


class Body
{
    public:
        Body();
        ~Body();

        //FUNCTIONS
        b2Body* getBody();
        void setDensity(float density);
        void setFriction(float friction);
        void setRestitution(float restitution);
        float getPositionX();
        float getPositionY();



    protected:

    private:
         //VARIABLES
        World *world = World::Instance();
        //b2World * world1 = nullptr;
        b2Body * bod = nullptr;
        b2BodyDef bodDef;
        b2Fixture * fix = nullptr;//Igualar a null
        b2FixtureDef fixDef;
};

#endif // BODY_H

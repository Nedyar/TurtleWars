#include "Body.h"

Body::Body()
{

    //Define body
    bodDef.type = b2BodyType::b2_dynamicBody;
    bodDef.position = b2Vec2(50.f,50.f);

    //Create body
    bod = world->CreateBody(bodDef);

    //Collider form
    b2PolygonShape shape;
    shape.SetAsBox(5.f,5.f);

    //Propertis of collider
    fixDef.shape = &shape;
    fixDef.density = 1.f;
    fixDef.friction = 0.f;
    fixDef.restitution = 0.0f;
    fix = bod->CreateFixture(&fixDef);

}


Body::Body(b2BodyType type,b2Vec2 spawn, b2CircleShape shape)
{
    bodDef.type = type;
    bodDef.position = spawn;
    //Create body
    bod = world->CreateBody(bodDef);

    //Propertis of collider
    fixDef.shape = &shape;
    fixDef.density = 1.f;
    fixDef.friction = 0.f;
    fixDef.restitution = 0.0f;
    fix = bod->CreateFixture(&fixDef);

}

Body::Body(b2BodyType type,b2Vec2 spawn, b2PolygonShape shape)
{
    bodDef.type = type;
    bodDef.position = spawn;
    //Create body
    bod = world->CreateBody(bodDef);

    //Propertis of collider
    fixDef.shape = &shape;
    fixDef.density = 1.f;
    fixDef.friction = 0.f;
    fixDef.restitution = 0.0f;
    fix = bod->CreateFixture(&fixDef);

}



b2Body* Body::getBody()
{
    return bod;
}

// ### INITIALITION ###





// ### PROPERTIES ###

void Body::setDensity(float density)
{
    fixDef.density = density;
}

void Body::setFriction(float friction)
{
    fixDef.friction = friction;
}

void Body::setRestitution(float restitution)
{
    fixDef.restitution = restitution;
}



// ### GETTERS and SETTERS ##


float Body::getPositionX()
{

    return bod->GetPosition().x;
}

float Body::getPositionY()
{
    return bod->GetPosition().y;
}




Body::~Body()
{
    if(world)
        delete world;
    //if(bod)
    //delete bod;
    //if(fix)
    //delete fix;



}

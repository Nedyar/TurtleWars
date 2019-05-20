#include "Physics2D.h"

#define DIVIDER 100.f



Physics2D* Physics2D::instance = nullptr;

Physics2D* Physics2D::Instance()
{
    if(!instance)
    {
        instance = new Physics2D;
    }

    return instance;
}

Physics2D::Physics2D()
{

}

Body* Physics2D::createRectangleBody(float positionX, float positionY, float width, float height, int pType)
{

    b2BodyType type;
    b2Vec2  spawn;
    b2PolygonShape shape;


    float density = 1.f;
    float friction = 3.1f;
    float restitution = 0.f;
    int group = 0;
    bool sensor = false;
    bool avoidRotate = true;


    type = b2BodyType::b2_staticBody;
    if(pType == 1)
        type = b2BodyType::b2_dynamicBody;
    if(pType == 2)
        type = b2BodyType::b2_kinematicBody;


    shape.SetAsBox(width/DIVIDER/2,height/DIVIDER/2);
    spawn = b2Vec2({positionX/DIVIDER,(positionY/DIVIDER)});


    Body *body = new Body(type, spawn, shape, density, friction, restitution, group, sensor, avoidRotate);
    return body;
}

Body* Physics2D::createCharacterBody(float positionX, float positionY, float width, float height, float pfriction)
{
    b2BodyType type;
    b2Vec2  spawn;
    b2PolygonShape shape;

    float density = 1.f;
    float friction = pfriction;
    float restitution = 0.f;
    int group = -1;
    bool avoidRotate = true;

    type = b2BodyType::b2_dynamicBody;
    //height-=4;
    width-=8;
    height-=3;
    shape.SetAsBox(width/DIVIDER/2,height/DIVIDER/2);
    spawn = b2Vec2({positionX/DIVIDER,(positionY/DIVIDER)});

    Body *body = new Body(type, spawn, shape, density, friction, restitution, group, avoidRotate);
    return body;
}




Body* Physics2D::createSpawnBody(float positionX, float positionY, float width, float height)
{
    b2BodyType type;
    b2Vec2  spawn;
    b2PolygonShape shape;

    float density = 1.f;
    float friction = 0.1;
    float restitution = 0.f;
    int group = -1;
    bool sensor = true;
    bool avoidRotate = false;


    type = b2BodyType::b2_kinematicBody;
    shape.SetAsBox(width/DIVIDER/2,(height-2)/DIVIDER/2);
    //ajuste en posY porque el centro del spawn esta en la mitd de la base
    spawn = b2Vec2({positionX/DIVIDER,(positionY/DIVIDER)});



    Body *body = new Body(type, spawn, shape, density, friction, restitution, group, sensor, avoidRotate);
    return body;
}

Body* Physics2D::createWeaponBody(float positionX, float positionY, float width, float height)
{
    b2BodyType type;
    b2Vec2  spawn;
    b2PolygonShape shape;

    float density = 1.f;
    float friction = 0.1f;
    float restitution = 0.f;
    int group = -1;
    bool sensor = false;
    bool avoidRotate = false;

    type = b2BodyType::b2_dynamicBody;
    shape.SetAsBox(width/DIVIDER/2,height/DIVIDER/2);
    spawn = b2Vec2({positionX/DIVIDER,(positionY/DIVIDER)});

    Body *body = new Body(type, spawn, shape, density, friction, restitution, group, sensor, avoidRotate);

    return body;
}

Body* Physics2D::createGrenadeBody(float positionX, float positionY, float width)
{
    b2BodyType type;
    b2Vec2  spawn;
    b2CircleShape shape;

    float density = 9.f;
    float friction = 99.5f;
    float restitution = 0.5f;
    int group = -1;
    bool sensor = false;
    bool avoidRotate = false;

    type = b2BodyType::b2_dynamicBody;
    shape.m_radius = width/DIVIDER/2;
    spawn = b2Vec2({positionX/DIVIDER,(positionY/DIVIDER)});

    Body *body = new Body(type, spawn, shape, density, friction, restitution, group, sensor, avoidRotate);

    return body;
}


Body* Physics2D::createBulletBody(float positionX, float positionY)
{
    b2BodyType type;
    b2Vec2  spawn;
    b2PolygonShape shape;

    float density = 0.f;
    float friction = 0.1f;
    float restitution = 0.f;
    int group = -2;
    bool sensor = false;
    bool avoidRotate = false;

    type = b2BodyType::b2_dynamicBody;
    shape.SetAsBox(.1/DIVIDER,.1/DIVIDER);
    spawn = b2Vec2({positionX/DIVIDER,(positionY/DIVIDER)});

    Body *body = new Body(type, spawn, shape, density, friction, restitution, group, sensor, avoidRotate);
    body->getBody()->SetGravityScale(0);
    return body;
}


void Physics2D::updateWorld()
{
    world->update();
}

void Physics2D::resetWorld()
{
    world->reset();
}

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
    //bod = new Body();
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

    /* shape.SetAsBox(sprite.getGlobalBounds().width/DIVIDER/2,sprite.getGlobalBounds().height/DIVIDER/2);
    spawn = b2Vec2({sprite.getPosition().x/DIVIDER,(sprite.getPosition().y/DIVIDER)});*/



    Body *body = new Body(type, spawn, shape, density, friction, restitution, group, sensor, avoidRotate);
    return body;
}

Body* Physics2D::createCharacterBody(float positionX, float positionY)
{
    b2BodyType type;
    b2Vec2  spawn;
    b2PolygonShape shape;

    float width = 10.f;
    float height = 30.f;
    float density = 1.f;
    float friction = 0.1f;
    float restitution = 0.f;
    int group = -1;
    bool sensor = false;
    bool avoidRotate = true;

    type = b2BodyType::b2_dynamicBody;
    shape.SetAsBox(width/DIVIDER/2,height/DIVIDER/2);
    spawn = b2Vec2({positionX/DIVIDER,(positionY/DIVIDER)});

    Body *body = new Body(type, spawn, shape, density, friction, restitution, group, sensor, avoidRotate);
    return body;
}

Body* Physics2D::createSpawnBody(float positionX, float positionY)
{
    b2BodyType type;
    b2Vec2  spawn;
    b2PolygonShape shape;

    float width = 30.f;
    float height = 20.f;
    float density = 1.f;
    float friction = 0.1f;
    float restitution = 0.f;
    int group = 0;
    bool sensor = true;
    bool avoidRotate = false;


    type = b2BodyType::b2_kinematicBody;
    shape.SetAsBox(width/DIVIDER/2,height/DIVIDER/2);
    //ajuste en posY porque el centro del spawn esta en la mitd de la base
    spawn = b2Vec2({positionX/DIVIDER,((positionY-(height/2.f+2))/DIVIDER)});



    Body *body = new Body(type, spawn, shape, density, friction, restitution, group, sensor, avoidRotate);
    return body;
}

Body* Physics2D::createGunBody(float positionX, float positionY)
{
    b2BodyType type;
    b2Vec2  spawn;
    b2PolygonShape shape;

    float width = 10.f;
    float height = 10.f;
    float density = 1.f;
    float friction = 0.1f;
    float restitution = 0.f;
    int group = 0;
    bool sensor = false;
    bool avoidRotate = false;

    type = b2BodyType::b2_dynamicBody;
    shape.SetAsBox(width/DIVIDER/2,height/DIVIDER/2);
    spawn = b2Vec2({positionX/DIVIDER,(positionY/DIVIDER)});

    Body *body = new Body(type, spawn, shape, density, friction, restitution, group, sensor, avoidRotate);
    return body;
}

void Physics2D::updateWorld()
{
    World::Instance()->update();
}

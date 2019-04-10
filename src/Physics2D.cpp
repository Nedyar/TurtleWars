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


    if(pType == 1)
        type = b2BodyType::b2_dynamicBody;
    if(pType == 0)
        type = b2BodyType::b2_staticBody;
    if(pType == -1)
        type = b2BodyType::b2_kinematicBody;



    shape.SetAsBox(width/DIVIDER/2,height/DIVIDER/2);
    spawn = b2Vec2({positionX/DIVIDER,(positionY/DIVIDER)});

        std::cout <<"Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "X: " << positionX << std::endl;
    std::cout << "Y: " << positionY << std::endl;
    /* shape.SetAsBox(sprite.getGlobalBounds().width/DIVIDER/2,sprite.getGlobalBounds().height/DIVIDER/2);
    spawn = b2Vec2({sprite.getPosition().x/DIVIDER,(sprite.getPosition().y/DIVIDER)});*/

    Body *body = new Body(type, spawn, shape);
    return body;
}


void Physics2D::updateWorld()
{
    World::Instance()->update();
}

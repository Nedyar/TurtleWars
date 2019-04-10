#include "Physics2D.h"



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


Body* Physics2D::createCircleBody(sf::Sprite &sprite,float pSize, int pType)
{

    // Body Type
    type = b2BodyType::b2_dynamicBody;
    if(pType == 0)
        type = b2BodyType::b2_staticBody;
    if(pType == -1)
        type = b2BodyType::b2_kinematicBody;

    // Body Shape
    b2CircleShape shape;
    shape.m_radius = pSize;

    spawn = b2Vec2({sprite.getPosition().x,sprite.getPosition().y});


    body = new Body(type, spawn, shape);
    return body;

}


Body* Physics2D::createRectangleBody(sf::Sprite &sprite,float pSize, int pType)
{

    // Body Type
    type = b2BodyType::b2_dynamicBody;
    if(pType == 0)
        type = b2BodyType::b2_staticBody;
    if(pType == -1)
        type = b2BodyType::b2_kinematicBody;

    // Body Shape
    b2PolygonShape shape;

    float offset = sprite.getLocalBounds().width/sprite.getLocalBounds().height;
    if (offset < 0)
        shape.SetAsBox(pSize*offset,pSize);
    else
        shape.SetAsBox(pSize,pSize*offset);

    // aplicar ajuste mas tarde tamSprite.x/tamSprite.y, if(res<0) = pSizeX*res  y lo contrario

    sprite.getPosition().x;

    // Body Spawn
    spawn = b2Vec2({sprite.getPosition().x,sprite.getPosition().y});


    body = new Body(type, spawn, shape);
    return body;

}








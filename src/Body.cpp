#include "Body.h"

#define MULTIPLIER 100.f

Body::Body(b2BodyType type,b2Vec2 spawn, b2CircleShape shape)
{

    b2BodyDef bodDef;
    b2FixtureDef fixDef;
    bodDef.type = type;
    bodDef.position = spawn;
    //Create body
    bod = world->CreateBody(bodDef);

    //Propertis of collider
    fixDef.shape = &shape;
    fixDef.density = 1.f;
    fixDef.friction = 0.1f;
    fixDef.restitution = 0.0f;
    fix = bod->CreateFixture(&fixDef);

}

Body::Body(b2BodyType type,b2Vec2 spawn, b2PolygonShape shape)
{
    // will deprecate
    collideShape = shape;
    b2BodyDef bodDef;
    b2FixtureDef fixDef;

    bodDef.type = type;
    bodDef.position = spawn;
    //Create body
    bod = world->CreateBody(bodDef);

    //Propertis of collider
    fixDef.shape = &shape;
    fixDef.density = 1.f;
    fixDef.friction = 0.1f;
    fixDef.restitution = 0.0f;
    fix = bod->CreateFixture(&fixDef);

}

sf::RectangleShape Body::dameRect(){
    sf::RectangleShape Polygon(sf::Vector2f((collideShape.GetVertex(2).x-collideShape.GetVertex(0).x)*MULTIPLIER,(collideShape.GetVertex(2).y-collideShape.GetVertex(0).y)*MULTIPLIER));
    Polygon.setFillColor(sf::Color::Transparent);
    Polygon.setOutlineThickness(1);
    Polygon.setOrigin(Polygon.getSize().x/2,Polygon.getSize().y/2);
    Polygon.setPosition(getPositionX(),getPositionY());

    return Polygon;
}


b2Body* Body::getBody(){
    return bod;
}

// ### PROPERTIES ###

void Body::setDensity(float density){
    fix->SetDensity(density);
}

void Body::setFriction(float friction){
    std::cout << bod->GetFixtureList()[0].GetFriction() << std::endl;


    /*bod->DestroyFixture(fix);

    b2FixtureDef fixDef;
    fixDef.shape = fix->GetShape();
    fixDef.density = fix->GetDensity();
    fixDef.friction = friction;
    fixDef.restitution = fix->GetRestitution();

    fix = bod->CreateFixture(&fixDef);*/
    fix->SetFriction(friction);


    std::cout << bod->GetFixtureList()[0].GetFriction() << std::endl;
}

void Body::setRestitution(float restitution){
    fix->SetRestitution(restitution);
}



// ### GETTERS and SETTERS ##


float Body::getPositionX(){

   return bod->GetPosition().x*MULTIPLIER;
}

float Body::getPositionY(){
   return bod->GetPosition().y*MULTIPLIER;
}







Body::~Body()
{

}

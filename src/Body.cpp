#include "Body.h"

#define MULTIPLIER 100.f

///Create default body
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

///Create a body whith a properties
Body::Body(b2BodyType type,b2Vec2 spawn, b2PolygonShape shape, float density, float friction,float restitution, int group, bool avoidRotate)
{

    collideShape = shape;//save a shape
    b2BodyDef bodDef;
    b2FixtureDef fixDef;


    bodDef.type = type;
    bodDef.position = spawn;
    //Create body
    bod = world->CreateBody(bodDef);


    //PHYSIS PROPERTIE
    fixDef.filter.groupIndex = group;



    fixDef.shape = &shape;
    fixDef.density = density;
    fixDef.friction = friction;
    fixDef.restitution = restitution;
    fix = bod->CreateFixture(&fixDef);

    bod->SetFixedRotation(avoidRotate);

}


///Return a SFML rectangle to graw collider in window
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

b2Body* Body::setFriction(b2Body* body, float friction){
/*
    b2BodyType type = body.GetType();
    b2Vec2 spawn = body.GetPosition();
    b2PolygonShape shape;
    float density;
    float friction;
    float restitution;


    b2BodyDef bodDef;
    b2FixtureDef fixDef;

    bodDef.type = body.GetType();
    bodDef.position = body.GetPosition();
    //Create body
    bod = world->CreateBody(bodDef);

    //Propertis of collider
    fixDef.shape = &shape;
    fixDef.density = density;
    fixDef.friction = friction;
    fixDef.restitution = restitution;
    fix = bod->CreateFixture(&fixDef);
*/
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

void Body::avoidRotate(){
    bod->SetAngularVelocity(0.f);//aboid rotating
}

float Body::getAngle(){
    return rad2deg(bod->GetAngle());
}


 float Body::rad2deg(float rad){
    float pi = 3.14;
    return rad / pi * 180;
}









Body::~Body()
{

}

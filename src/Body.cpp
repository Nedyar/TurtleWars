#include "Body.h"
#include <iostream>
using namespace std;

#define MULTIPLIER 100.f



///Create a body whith a properties
Body::Body(b2BodyType type,b2Vec2 spawn, b2PolygonShape shape, float density, float friction,float restitution, int group, bool sensor,  bool avoidRotate, double angle)
{

    collideShape = shape;//save a shape
    b2BodyDef bodDef;
    b2FixtureDef fixDef;


    bodDef.type = type;
    bodDef.position = spawn;
    bodDef.angle = angle;
    bodDef.fixedRotation = avoidRotate;
    //Create body
    bod = World::Instance()->CreateBody(bodDef);


    fixDef.filter.groupIndex = group;
    //fixDef.filter.categoryBits = category;
    //fixDef.filter.maskBits = mask;
    fixDef.isSensor = sensor;

    fixDef.shape = &shape;
    fixDef.density = density;
    fixDef.friction = friction;
    fixDef.restitution = restitution;
    fix = bod->CreateFixture(&fixDef);

    //bod->SetFixedRotation(avoidRotate);
    //bod->SetTransform(spawn, angle);

}

Body::Body(b2BodyType type,b2Vec2 spawn, b2PolygonShape shape, float density, float friction,float restitution, int group,  bool avoidRotate)
{

    collideShape = shape;//save a shape
    b2BodyDef bodDef;
    b2FixtureDef fixDef;


    bodDef.type = type;
    bodDef.position = spawn;
    //Create body
    bod = World::Instance()->CreateBody(bodDef);
    bod->SetFixedRotation(avoidRotate);

    //fixDef.filter.categoryBits = category;
    //fixDef.filter.maskBits = mask;
    fixDef.shape = &shape;
    fixDef.density = density;
    fixDef.friction = friction;
    fixDef.restitution = restitution;
    fixDef.isSensor = true;
    fix = bod->CreateFixture(&fixDef);

    fixDef.filter.groupIndex = group;

    fixDef.isSensor = false;
    fix = bod->CreateFixture(&fixDef);

}

Body::Body(b2BodyType type, b2Vec2 spawn, b2CircleShape shape, float density, float friction,float restitution, int group, bool sensor,  bool avoidRotate)
{
    collideShape.SetAsBox(0.05,0.05);//cuadrado de mentira

    b2BodyDef bodDef;
    b2FixtureDef fixDef;

    bodDef.type = type;
    bodDef.position = spawn;
    //bodDef.fixedRotation = avoidRotate;
    bod = World::Instance()->CreateBody(bodDef);

    fixDef.filter.groupIndex = group;
    //fixDef.isSensor = sensor;
    fixDef.shape = &shape;
    fixDef.density = density;
    fixDef.friction = friction;
    fixDef.restitution = restitution;
    fix = bod->CreateFixture(&fixDef);


    cout << "Granada creada" << endl;
    cout << "Angulo de la granada: "<<bod->GetAngle() << endl;
    cout << "Pos x: " << spawn.x << endl;




}

Body::~Body()
{
    cout << "borrando body:" << bod << endl;
    World::Instance()->destroyBody(bod);
    //world->update();
}


///Return a SFML rectangle to graw collider in window
void Body::pintaRect(sf::RenderWindow &app){

    sf::RectangleShape Polygon(sf::Vector2f((collideShape.GetVertex(2).x-collideShape.GetVertex(0).x)*MULTIPLIER,(collideShape.GetVertex(2).y-collideShape.GetVertex(0).y)*MULTIPLIER));
    Polygon.setFillColor(sf::Color::Transparent);
    Polygon.setOutlineThickness(1);
    Polygon.setOrigin(Polygon.getSize().x/2,Polygon.getSize().y/2);
    Polygon.setPosition(getPositionX(),getPositionY());

    app.draw(Polygon);

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

void Body::setUserData(void* userData){
    bod->SetUserData(userData);
}

float Body::getAngle(){
    if(bod==nullptr){
        cout << "el puto body es null" << endl;
    }
    return rad2deg(bod->GetAngle());

}

float Body::rad2deg(float rad){
    cout << "entra en el metodo de conversion" << endl;
    float pi = 3.14;
    return rad / pi * 180;
}

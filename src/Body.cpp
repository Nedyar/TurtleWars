#include "Body.h"

Body::Body()
{
    //world1 = new b2World(b2Vec2(0.f,195.f));//GRAVITY EN X  AND Y
    //Get Phisic World

    //Define body
    bodDef.type = b2BodyType::b2_dynamicBody;
    bodDef.position = b2Vec2(50.f,50.f);

    //Create body
    //bod = world1->CreateBody(&bodDef);
    bod = world->CreateBody(bodDef);


    //Collider form
    b2PolygonShape shape;
    shape.SetAsBox(50.f,5.f);

    //Propertis of collider
    fixDef.shape = &shape;
    fixDef.density = 1.f;
    fixDef.friction = 0.f;
    fixDef.restitution = 0.0f;


    fix = bod->CreateFixture(&fixDef);

}

b2Body* Body::getBody(){
    return bod;
}

void Body::setDensity(float density){
    fixDef.density = density;
}

void Body::setFriction(float friction){
    fixDef.friction = friction;
}

void Body::setRestitution(float restitution){
    fixDef.restitution = restitution;
}

float Body::getPositionX(){
   return bod->GetPosition().x;
}

float Body::getPositionY(){
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

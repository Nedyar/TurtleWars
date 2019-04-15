#include "World.h"
#include <EventCollider.h>

#include <iostream>
using namespace std;


World* World::instance = 0;
World* World::Instance()
{
    if(instance == 0)
    {
        //instance = new b2World(b2Vec2(0.f,195.f));//
        instance = (World*)malloc(sizeof(World));
        instance = new World();


    }
    return instance;
}

World::World()
{
    world2D  = (b2World*)malloc(sizeof(b2World));
    world2D = new b2World(b2Vec2(0.f,9.8f));
    world2D->SetContactListener(EventCollider::Instance());
}

b2Body* World::CreateBody(b2BodyDef bodDef) //COmprobar que esta funcion devulve un puntero
{
    b2Body* body = world2D->CreateBody(&bodDef);
    return body;

}

void World::destroyBody(b2Body* body)
{
    //cout << "Intento borrar body del mundo: " << body << end;
    world2D->DestroyBody(body);
    cout << "He borrao del mundo " << endl;
}

void World::update()
{
    //cout << "Updateando world" << endl;
    world2D->Step((1.f/60.f), 8, 8);//8, 8 is the iterations (change to 12 fro test)
    //cout << "Updateando world" << endl;
}

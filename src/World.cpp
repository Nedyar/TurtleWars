#include "World.h"

World* World::instance = 0;
World* World::Instance()
{
    if(instance == 0)
    {
        //instance = new b2World(b2Vec2(0.f,195.f));//
        instance = new World();
        //world1 = new b2World(b2Vec2(0.f,195.f));//
    }
    return instance;
}

World::World()
{
    world2D = new b2World(b2Vec2(0.f,9.8f));
}

b2Body* World::CreateBody(b2BodyDef &bodDef){//COmprobar que esta funcion devulve un puntero
    b2Body* body = world2D->CreateBody(&bodDef);
    return body;

}

void World::destroyBody(b2Body* body){
   // world2D.DestroyBody(body);
}

void World::update(){
    world2D->Step((1.f/60.f), 8, 8);//8, 8 is the iterations (change to 12 fro test)
    world2D->ClearForces();
}



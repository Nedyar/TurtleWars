#ifndef WORLD_H
#define WORLD_H

#include <Box2D/Box2D.h>
//#include <Phisics2D.h>



class World
{
public:
    static World* Instance();
    b2Body* CreateBody(b2BodyDef&);
    //~World();
protected:
    World();
    World(const World & );
    World &operator= (const World & );

private:
    static World* instance;
    b2World * world2D;
    b2Body * body = nullptr;

};

#endif // WORLD_H







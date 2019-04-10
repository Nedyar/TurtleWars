#ifndef WORLD_H
#define WORLD_H

#include <Box2D/Box2D.h>

class World
{
    public:
        static World* Instance();
        b2Body* CreateBody(b2BodyDef&);
        void update();
        //~World();
    protected:
        World();
        World(const World & );
        World &operator= (const World & );

    private:
        static World* instance;
        b2World * world2D;
};

#endif // WORLD_H

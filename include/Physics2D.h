#ifndef PHYSICS2D_H
#define PHYSICS2D_H

#include <Body.h>
#include <SFML/Graphics.hpp> // cuando me coma la polla esto se borra



class Physics2D
{
    public:
        static Physics2D* Instance();
        Body* createRectangleBody(float positionX, float positionY, float width, float height, int pType = 0);

        Body* createCharacterBody(float positionX, float positionY, float width, float height);
        Body* createSpawnBody(float positionX, float positionY, float width, float height);
        Body* createWeaponBody(float positionX, float positionY, float width, float height);
        Body* createGrenadeBody(float positionX, float positionY, float width);
        Body* createBulletBody(float positionX, float positionY);
        void updateWorld();
        void resetWorld();

        //~Physics2D();
    protected:
        Physics2D();
        Physics2D(const Physics2D & );
        Physics2D &operator= (const Physics2D &);

    private:
        static Physics2D* instance;
        World* world = World::Instance();

};

#endif // PHYSICS2D_H

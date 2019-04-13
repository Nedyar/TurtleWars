#include "EventCollider.h"

#include <iostream>
using namespace std;

EventCollider* EventCollider::instance = 0;
EventCollider* EventCollider::Instance()
{
    if(instance == 0)
    {
        instance = new EventCollider();
    }
    return instance;
}

EventCollider::EventCollider()
{
}



void EventCollider::BeginContact(b2Contact* contact)
{

    Collidable * objA = (Collidable*)contact->GetFixtureA()->GetBody()->GetUserData();
    Collidable * objB = (Collidable*)contact->GetFixtureB()->GetBody()->GetUserData();

    if (objA)
        if (objA->getId() == 1)
        //cout << "juju" << endl;
        {
            Character* player = (Character*) objA;
            switch (objB->getId())
            {
            case 2: // WeaponSpawner
                player->setWeaponSpawnerOver((WeaponSpawner*)objB);
                break;
            case 3: // Weapon
                break;
            case 4: // Bullet
                break;
            default:
                player->setWeaponSpawnerOver(nullptr);
                break;
            }
        }
    if (objB)
        switch (objB->getId())
        {

        }
}

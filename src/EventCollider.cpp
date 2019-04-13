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
        {
            switch (objB->getId())
            {

            }
        }
    if (objB)
        switch (objB->getId())
        {

        }
}

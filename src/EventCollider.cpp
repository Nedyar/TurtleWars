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

    if (objA && objB)
        if (objA->getId() == 1)
        {
            Character* player = (Character*) objA;
            switch (objB->getId())
            {
            case 2: // WeaponSpawner
                player->setWeaponSpawnerOver((WeaponSpawner*)objB);
                cout << "Un ws"<< endl;
                break;
            case 3: // Weapon
                player->setWeaponOver((Weapon*)objB);
                cout << "Un arma"<< endl;
                break;
            case 4: // Bullet
                player->die();
                //delete (Bullet*)objB;
                break;
            }
        }
        else if (objB->getId() == 1)
        {
            Character* player = (Character*) objB;
            switch (objA->getId())
            {
            case 2: // WeaponSpawner
                player->setWeaponSpawnerOver((WeaponSpawner*)objA);
                cout << "Un ws"<< endl;
                break;
            case 3: // Weapon
                player->setWeaponOver((Weapon*)objA);
                cout << "Un arma"<< endl;
                break;
            case 4: // Bullet
                player->die();
                //delete (Bullet*)objA;
                break;
            }
        }
        // el objeto a es bala, hacer desaparecer
        else if (objA->getId() == 4)
        {
            cout << "Bala choca"<< endl;;
            if (objB->getId() < 1 || objB->getId() > 4)
            {
                //delete (Bullet*)objA;
            }
        }
         // el objeto b es bala, hacer desaparecer
        else if (objB->getId() == 4)
        {
            cout << "Bala choca"<< endl;;
            if (objA->getId() < 1 || objA->getId() > 4)
            {
                //delete (Bullet*)objB;
            }
        }
}

void EventCollider::EndContact(b2Contact* contact)
{

    Collidable * objA = (Collidable*)contact->GetFixtureA()->GetBody()->GetUserData();
    Collidable * objB = (Collidable*)contact->GetFixtureB()->GetBody()->GetUserData();

    if (objA && objB)
        if (objA->getId() == 1)
            //cout << "juju" << endl;
        {
            Character* player = (Character*) objA;
            switch (objB->getId())
            {
            case 2: // WeaponSpawner
                player->setWeaponSpawnerOver(nullptr);
                cout << "salgo" <<endl;
                break;
            case 3: // Weapon
                player->setWeaponOver(nullptr);
                cout << "me separo del arma" <<endl;
                break;
            case 4: // Bullet
                break;
            }
        }
}

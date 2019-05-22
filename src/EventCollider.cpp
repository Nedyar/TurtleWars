#include "EventCollider.h"

//#include <iostream>
//using namespace std;

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
    //cout << "contacto detectado" << endl;
    Collidable * objA = (Collidable*)contact->GetFixtureA()->GetBody()->GetUserData();
    Collidable * objB = (Collidable*)contact->GetFixtureB()->GetBody()->GetUserData();

    if (objA && objB)
    {
        if (objA->getId() == 1)
        {
            //cout << "Personaje es A" << endl;
            Character* player = (Character*) objA;
            switch (objB->getId())
            {
            case 2: // WeaponSpawner
                //cout << "WaponSpawner es B" << endl;
                player->setWeaponSpawnerOver((WeaponSpawner*)objB);
                //cout << "Un ws"<< endl;
                break;
            case 3: // Weapon
                //cout << "Weapon es B" << endl;
                player->addWeaponOver((Weapon*)objB);
                //cout << "Un arma"<< endl;
                break;
            case 4: // Bullet
                //cout << "Bullet es B" << endl;
                player->kill();
                ((Bullet*) objB)->deleteMe();
                break;
            }
        }
        else if (objB->getId() == 1)
        {
            //cout << "Personaje es B" << endl;
            Character* player = (Character*) objB;
            switch (objA->getId())
            {
            case 2: // WeaponSpawner
                //cout << "WaponSpawner es A" << endl;
                player->setWeaponSpawnerOver((WeaponSpawner*)objA);
                //cout << "Un ws"<< endl;
                break;
            case 3: // Weapon
                //cout << "Weapon es A" << endl;
                player->addWeaponOver((Weapon*)objA);
                //cout << "Un arma"<< endl;
                break;
            case 4: // Bullet
                //cout << "Bullet es A" << endl;
                player->kill();
                ((Bullet*) objA)->deleteMe();
                break;
            }
        }
    }
    else if (objA)
    {
        if (objA->getId() == 4)
        {
            ((Bullet*) objA)->deleteMe();
        }
    }
    else if (objB)
    {
        if (objB->getId() == 4)
        {
            ((Bullet*) objB)->deleteMe();
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
                //cout << "salgo" <<endl;
                break;
            case 3: // Weapon
                player->removeWeaponOver((Weapon*)objB);
                //cout << "me separo del arma" <<endl;
                break;
            case 4: // Bullet
                break;
            }
        }
        else if (objB->getId() == 1)
            //cout << "juju" << endl;
        {
            Character* player = (Character*) objB;
            switch (objA->getId())
            {
            case 2: // WeaponSpawner
                player->setWeaponSpawnerOver(nullptr);
                //cout << "salgo" <<endl;
                break;
            case 3: // Weapon
                player->removeWeaponOver((Weapon*)objA);
                //cout << "me separo del arma" <<endl;
                break;
            case 4: // Bullet
                break;
            }
        }
}

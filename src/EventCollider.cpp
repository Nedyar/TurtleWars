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
    //bodyA = new b2Body();

}



void EventCollider::BeginContact(b2Contact* contact)
{

    Character * characterA    = (Character*)contact->GetFixtureA()->GetBody()->GetUserData();
    WeaponSpawner* wSpawnerA  = (WeaponSpawner*)contact->GetFixtureA()->GetBody()->GetUserData();
    Character * characterB    = (Character*)contact->GetFixtureB()->GetBody()->GetUserData();
    WeaponSpawner* wSpawnerB  = (WeaponSpawner*)contact->GetFixtureB()->GetBody()->GetUserData();

    if (characterA && wSpawnerA)
    {
          cout << "Charactera - WeaponSpawnera" << endl;
    }

    if (characterA && wSpawnerB)
    {
          cout << "Charactera - WeaponSpawnerb" << endl;
    }



    if (characterB && wSpawnerA)
    {
          cout << "Characterb - WeaponSpawnera" << endl;
    }

    if (characterB && wSpawnerB)
    {
          cout << "Characterb - WeaponSpawnerb" << endl;
    }
/*
    Collitionable * objA = (Character*)contact->GetFixtureA()->GetBody()->GetUserData();
    Collitionable * objB = (Character*)contact->GetFixtureB()->GetBody()->GetUserData();

    if (objA && objB)
    {
        cout << objB->getId() << endl;
        cout << objA->getId() << endl;
    }

    objA = (WeaponSpawner*)contact->GetFixtureA()->GetBody()->GetUserData();
    objB = (Character*)contact->GetFixtureB()->GetBody()->GetUserData();

    if (objA && objB)
    {
        cout << objB->getId() << endl;
        cout << objA->getId() << endl;
    }

    objA = (Character*)contact->GetFixtureA()->GetBody()->GetUserData();
    objB = (WeaponSpawner*)contact->GetFixtureB()->GetBody()->GetUserData();

    if (objA && objB)
    {
        cout << objB->getId() << endl;
        cout << objA->getId() << endl;
    }*/

}

/*void EventCollider::BeginContact(b2Contact* contact)
{

    //Collitionable * objA = (Collitionable*)contact->GetFixtureA()->GetBody()->GetUserData();
    Collitionable * objB = (Collitionable*)contact->GetFixtureB()->GetBody()->GetUserData();

    cout << objB << endl;
    //cout << contact->GetFixtureB()->GetBody()->GetUserData() << endl;

    cout << &typeid(contact->GetFixtureB()->GetBody()->GetUserData()) << endl;
    cout << &typeid(Character*) << endl;


    /*if (typeid((objB)) == typeid(Character*)) {
        cout << "juju" << endl;
    }*/


/*if (typeid(dynamic_cast<Character*>(objA)) == typeid(Character*)) {
    cout << "juju" << endl;
}*/










/*

    Character * objA  = (Character*)bodyA->GetUserData();
    Character * objB = (Character*)bodyB->GetUserData();

    //Recasteo
    if(objA)
    {
        cout << ((Character *)objA)->getId() << endl;
       ((Character *)objA)->die();

        Character * objC  = (Character*)objA;
        cout << objC->getId() << endl;
    }
    if(objB)
    {
        cout << ((Character *)objB)->getId() << endl;
       ((Character *)objB)->die();
    }


    // cout << objB->getId() << endl;

    /*
    if (Collitionable * objA = (Collitionable*)bodyA->GetUserData()){
    if(Collitionable * objB = (Collitionable*)bodyB->GetUserData()){
       cout << "Character to Spawn1" << endl;
    }
    }



    //if (typeid(dynamic_cast<Grenade*>(weapon)) == typeid(Gun*))










    /*

    b2Body * bodyA = contact->GetFixtureA()->GetBody();
    b2Body * bodyB = contact->GetFixtureB()->GetBody();
    std::string * u = (std::string*)bodyA->GetUserData();
    std::string * i = (std::string*)bodyB->GetUserData();

    // int u = (int)bodyA->GetUserData();

    if(u){
    cout << "Entra en EventCollider: " << u->c_str() << endl;
    }
    if(i){
    cout << "Entra en EventCollider: " << i->c_str() << endl;
    }

    */
/*
    if (juego * objA = (juego*)contact->GetFixtureA()->GetBody()->GetUserData())
	{
		if (juego * objB = (juego*)contact->GetFixtureB()->GetBody()->GetUserData())
		{
			cout << "juju" << endl;
		}
	}




//bodyA->SetActive(true);



//cout << "yokese" << endl;



}*/

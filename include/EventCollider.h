#ifndef EVENTCOLLIDER_H
#define EVENTCOLLIDER_H
#include <Box2D/Box2D.h>

#include <Collitionable.h>
#include <Character.h>
#include <WeaponSpawner.h>




class EventCollider : public b2ContactListener
{
    public:
        static EventCollider* Instance();
        void BeginContact(b2Contact* contact);

    private:
        static EventCollider* instance;
        EventCollider();
        EventCollider(const EventCollider& cpy);
        EventCollider& operator=(const EventCollider& cpy);


};

#endif // EVENTCOLLIDER_H

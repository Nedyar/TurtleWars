#include "Weapon.h"

void Weapon::setPos(int x, int y)
{
    sprite.setPosition(x,y);
}

void Weapon::setFacingLeft(bool facing) {
    facingLeft = facing;
}

void Weapon::setOwner(Character* newOwner) {
    owner = newOwner;
}

Character* Weapon::getOwner() {
    return owner;
}

void Weapon::setXVelocity(float velocity)
{
    body->getBody()->SetLinearVelocity((b2Vec2(velocity,body->getBody()->GetLinearVelocity().y)));
}

void Weapon::setYVelocity(float velocity)
{
    body->getBody()->SetLinearVelocity((b2Vec2(0,velocity)));
}

void Weapon::resetClock() {
    clock.restart();
}

void Weapon::deleteBody()
{
    delete body;
    body = nullptr;
}

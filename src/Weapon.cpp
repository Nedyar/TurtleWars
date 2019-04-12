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

#include "Entity.h"

Entity::Entity(int x, int y, int h, int atk, std::string n)
    : pos{ x, y }, hp(h), maxHp(h), attackPower(atk), name(n) {}

bool Entity::isAlive() const {
    return hp > 0;
}

void Entity::takeDamage(int dmg) {
    hp -= dmg;
    if (hp < 0) hp = 0;
}
#pragma once
#include <string>

struct Point {
    int x, y;
};

class Entity {
public:
    Point pos;
    int hp;
    int maxHp;
    int attackPower;
    std::string name;

    Entity(int x, int y, int h, int atk, std::string n);
    
    // Check if alive
    bool isAlive() const;
    
    // Take damage
    void takeDamage(int dmg);
};
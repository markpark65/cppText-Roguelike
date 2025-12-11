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
    
    // 생존 여부 확인
    bool isAlive() const;
    
    // 데미지 입기
    void takeDamage(int dmg);
};
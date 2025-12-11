#pragma once
#include <vector>
#include <string>
#include "Entity.h"

class GameManager {
private:
    // 맵 설정
    const int MAP_WIDTH = 20;
    const int MAP_HEIGHT = 10;
    
    // 게임 상태
    std::vector<std::string> mapData;
    Entity* player;
    std::vector<Entity*> enemies;
    Point exitPos;
    
    bool isGameOver;
    bool isGameClear;
    std::string messageLog;

    // 내부 헬퍼 함수
    void InitMap();
    void MovePlayer(int dx, int dy);

public:
    GameManager();
    ~GameManager();

    void Run();          // 게임 루프 시작
    void Draw();         // 화면 렌더링
    void ProcessInput(); // 사용자 입력 처리
};
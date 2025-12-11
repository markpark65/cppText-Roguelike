#include "GameManager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h> // Windows 전용
#include <windows.h> // Windows 전용

using namespace std;

// 아이콘 상수
const char PLAYER_ICON = '@';
const char ENEMY_ICON = 'E';
const char WALL_ICON = '#';
const char EXIT_ICON = 'X';
const char EMPTY_ICON = '.';

GameManager::GameManager() : isGameOver(false), isGameClear(false), messageLog("게임 시작! 탈출구를 찾으세요.") {
    srand((unsigned int)time(0));
    InitMap();
}

GameManager::~GameManager() {
    delete player;
    for (auto e : enemies) delete e;
}

void GameManager::InitMap() {
    mapData.clear();
    // 벽과 빈 공간 생성
    for (int i = 0; i < MAP_HEIGHT; ++i) {
        string row = "";
        for (int j = 0; j < MAP_WIDTH; ++j) {
            if (i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH - 1)
                row += WALL_ICON;
            else
                row += EMPTY_ICON;
        }
        mapData.push_back(row);
    }

    player = new Entity(1, 1, 100, 10, "용사");
    exitPos = { MAP_WIDTH - 2, MAP_HEIGHT - 2 };

    // 적 랜덤 배치
    for (int i = 0; i < 3; ++i) {
        int rx = rand() % (MAP_WIDTH - 2) + 1;
        int ry = rand() % (MAP_HEIGHT - 2) + 1;
        if ((rx == player->pos.x && ry == player->pos.y) || (rx == exitPos.x && ry == exitPos.y)) {
            i--; continue;
        }
        enemies.push_back(new Entity(rx, ry, 30, 5, "고블린"));
    }
}

void GameManager::Draw() {
    // 커서 이동 (화면 깜빡임 최소화)
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Cur = { 0, 0 };
    SetConsoleCursorPosition(hOut, Cur);

    cout << "========================================" << endl;
    cout << " [ C++ Console Roguelike ] " << endl;
    cout << "========================================" << endl;

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            bool drawn = false;

            if (x == player->pos.x && y == player->pos.y) {
                cout << PLAYER_ICON; drawn = true;
            } else if (x == exitPos.x && y == exitPos.y) {
                cout << EXIT_ICON; drawn = true;
            }

            if (!drawn) {
                for (auto e : enemies) {
                    if (e->isAlive() && e->pos.x == x && e->pos.y == y) {
                        cout << ENEMY_ICON; drawn = true; break;
                    }
                }
            }
            if (!drawn) cout << mapData[y][x];
        }
        cout << endl;
    }
    cout << "========================================" << endl;
    cout << " HP: " << player->hp << " | ATK: " << player->attackPower << endl;
    cout << " LOG: " << messageLog << "                " << endl; // 공백으로 이전 로그 지움
}

void GameManager::ProcessInput() {
    if (_kbhit()) {
        char key = _getch();
        int dx = 0, dy = 0;
        switch (tolower(key)) {
        case 'w': dy = -1; break;
        case 's': dy = 1; break;
        case 'a': dx = -1; break;
        case 'd': dx = 1; break;
        case 'q': isGameOver = true; break;
        }
        if (dx != 0 || dy != 0) MovePlayer(dx, dy);
    }
}

void GameManager::MovePlayer(int dx, int dy) {
    int nextX = player->pos.x + dx;
    int nextY = player->pos.y + dy;

    if (mapData[nextY][nextX] == WALL_ICON) {
        messageLog = "벽입니다.";
        return;
    }

    for (auto e : enemies) {
        if (e->isAlive() && e->pos.x == nextX && e->pos.y == nextY) {
            int dmgToEnemy = player->attackPower;
            e->takeDamage(dmgToEnemy);
            messageLog = "공격! 적 HP: " + to_string(e->hp);
            
            if (e->isAlive()) {
                player->takeDamage(e->attackPower);
                messageLog += " / 반격당함! 내 HP: " + to_string(player->hp);
            } else {
                messageLog = "적을 처치했습니다!";
            }

            if (player->hp <= 0) {
                isGameOver = true; 
                messageLog = "사망했습니다..."; 
            }
            return;
        }
    }

    player->pos.x = nextX;
    player->pos.y = nextY;
    messageLog = "이동함.";

    if (player->pos.x == exitPos.x && player->pos.y == exitPos.y) {
        isGameClear = true;
        isGameOver = true;
    }
}

void GameManager::Run() {
    // 커서 숨김 처리
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CurInfo;
    CurInfo.dwSize = 1; CurInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &CurInfo);
    system("cls");

    while (!isGameOver) {
        Draw();
        ProcessInput();
        Sleep(50);
    }
    
    system("cls");
    if (isGameClear) cout << "\n*** MISSION COMPLETE ***\n";
    else cout << "\n*** GAME OVER ***\n";
    cout << "Final Log: " << messageLog << endl;
    
    // 종료 대기
    while(_kbhit()) _getch(); // 버퍼 비우기
    _getch();
}
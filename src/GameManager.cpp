#include "GameManager.h"
#include <conio.h> // Windows 전용
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <windows.h> // Windows 전용

using namespace std;

// 아이콘 상수
const char PLAYER_ICON = '@';
const char ENEMY_ICON = 'E';
const char WALL_ICON = '#';
const char EXIT_ICON = 'X';
const char EMPTY_ICON = '.';

GameManager::GameManager()
    : isGameOver(false), isGameClear(false),
      messageLog("Game Start! Find the exit.") {
  srand((unsigned int)time(0));
  InitMap();
}

GameManager::~GameManager() {
  // smart buffer handles deletion
}

void GameManager::InitMap() {
  mapData.clear();
  // Generate walls and empty spaces
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

  player = std::make_unique<Entity>(1, 1, 100, 10, "Hero");
  exitPos = {MAP_WIDTH - 2, MAP_HEIGHT - 2};

  // Random enemy placement
  for (int i = 0; i < 3; ++i) {
    int rx = rand() % (MAP_WIDTH - 2) + 1;
    int ry = rand() % (MAP_HEIGHT - 2) + 1;
    if ((rx == player->pos.x && ry == player->pos.y) ||
        (rx == exitPos.x && ry == exitPos.y)) {
      i--;
      continue;
    }
    enemies.push_back(std::make_unique<Entity>(rx, ry, 30, 5, "Goblin"));
  }
}

void GameManager::Draw() {
  // Move cursor (Minimize screen flickering)
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD Cur = {0, 0};
  SetConsoleCursorPosition(hOut, Cur);

  cout << "========================================" << endl;
  cout << " [ C++ Console Roguelike ] " << endl;
  cout << "========================================" << endl;

  for (int y = 0; y < MAP_HEIGHT; ++y) {
    for (int x = 0; x < MAP_WIDTH; ++x) {
      bool drawn = false;

      if (x == player->pos.x && y == player->pos.y) {
        cout << PLAYER_ICON;
        drawn = true;
      } else if (x == exitPos.x && y == exitPos.y) {
        cout << EXIT_ICON;
        drawn = true;
      }

      if (!drawn) {
        for (const auto &e : enemies) {
          if (e->isAlive() && e->pos.x == x && e->pos.y == y) {
            cout << ENEMY_ICON;
            drawn = true;
            break;
          }
        }
      }
      if (!drawn)
        cout << mapData[y][x];
    }
    cout << endl;
  }
  cout << "========================================" << endl;
  cout << " HP: " << player->hp << " | ATK: " << player->attackPower << endl;
  cout << " LOG: " << messageLog << "                "
       << endl; // Clear previous log with spaces
}

void GameManager::ProcessInput() {
  if (_kbhit()) {
    char key = _getch();
    int dx = 0, dy = 0;
    switch (tolower(key)) {
    case 'w':
      dy = -1;
      break;
    case 's':
      dy = 1;
      break;
    case 'a':
      dx = -1;
      break;
    case 'd':
      dx = 1;
      break;
    case 'q':
      isGameOver = true;
      break;
    }
    if (dx != 0 || dy != 0)
      MovePlayer(dx, dy);
  }
}

void GameManager::MovePlayer(int dx, int dy) {
  int nextX = player->pos.x + dx;
  int nextY = player->pos.y + dy;

  if (mapData[nextY][nextX] == WALL_ICON) {
    messageLog = "It's a wall.";
    return;
  }

  for (const auto &e : enemies) {
    if (e->isAlive() && e->pos.x == nextX && e->pos.y == nextY) {
      int dmgToEnemy = player->attackPower;
      e->takeDamage(dmgToEnemy);
      messageLog = "Attack! Enemy HP: " + to_string(e->hp);

      if (e->isAlive()) {
        player->takeDamage(e->attackPower);
        messageLog += " / Countered! My HP: " + to_string(player->hp);
      } else {
        messageLog = "Enemy defeated!";
      }

      if (player->hp <= 0) {
        isGameOver = true;
        messageLog = "You died...";
      }
      return;
    }
  }

  player->pos.x = nextX;
  player->pos.y = nextY;
  messageLog = "Moved.";

  if (player->pos.x == exitPos.x && player->pos.y == exitPos.y) {
    isGameClear = true;
    isGameOver = true;
  }
}

void GameManager::Run() {
  // Hide cursor
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO CurInfo;
  CurInfo.dwSize = 1;
  CurInfo.bVisible = FALSE;
  SetConsoleCursorInfo(hOut, &CurInfo);
  system("cls");

  while (!isGameOver) {
    Draw();
    ProcessInput();
    Sleep(50);
  }

  system("cls");
  if (isGameClear)
    cout << "\n*** MISSION COMPLETE ***\n";
  else
    cout << "\n*** GAME OVER ***\n";
  cout << "Final Log: " << messageLog << endl;

  // Wait for exit
  while (_kbhit())
    _getch(); // Clear buffer
  _getch();
}
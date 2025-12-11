#pragma once
#include "Entity.h"
#include <memory>
#include <string>
#include <vector>

class GameManager {
private:
  // Map settings
  const int MAP_WIDTH = 20;
  const int MAP_HEIGHT = 10;

  // Game state
  std::vector<std::string> mapData;
  std::unique_ptr<Entity> player;
  std::vector<std::unique_ptr<Entity>> enemies;
  Point exitPos;

  bool isGameOver;
  bool isGameClear;
  std::string messageLog;

  // Internal helper functions
  void InitMap();
  void MovePlayer(int dx, int dy);

public:
  GameManager();
  ~GameManager();

  void Run();          // Start game loop
  void Draw();         // Render screen
  void ProcessInput(); // Process user input
};
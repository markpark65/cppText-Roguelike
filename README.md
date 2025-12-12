# C++ Text Roguelike

A console-based text roguelike game built using only C++ and the Standard Template Library (STL). This project mimics the structure of a dungeon crawler without relying on any external game engines, demonstrating pure Object-Oriented Programming (OOP) design.

## How to Play

You control the Player (P) to navigate the dungeon, defeat Monsters (M), and find the Exit (X).

- Movement: Use `W`, `A`, `S`, `D` keys to move Up, Left, Down, and Right.
- Combat: Moving into a monster's tile automatically triggers a turn-based attack.
- Victory: Reach the Exit (`X`) hidden somewhere in the map.
- Defeat: Game over if your HP drops to 0 during combat.

## Key Features

- Pure C++ Implementation: Runs natively in the Windows Console with zero external dependencies.
- Hybrid System: Real-time movement validation mixed with turn-based combat logic.
- Console UI: Split-screen rendering for the Map, Status (HP/ATK), and Combat Logs.
- OOP Architecture: Managed by a central `GameManager`, with `Entity` inheritance for Player and Monsters.

## Tech Stack

- Language: C++14 Standard
- Environment: Visual Studio, Windows Console API

## Project Structure

- `src/main.cpp`: Entry Point
- `src/GameManager.cpp`: Game Loop & Rendering System
- `src/Entity.cpp`: Character Logic (Player/Monster)
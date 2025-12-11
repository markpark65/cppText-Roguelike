# 🏰 C++ Text Roguelike (Console Game)

## 📖 프로젝트 소개
C++의 객체 지향 프로그래밍(OOP) 개념을 활용하여 제작한 **텍스트 기반 던전 크롤러 게임**입니다.
별도의 게임 엔진 없이 순수 C++와 표준 라이브러리(STL)만을 사용하여 게임 루프, 엔티티 관리, 충돌 처리 시스템을 구현하였습니다.

### 🎯 개발 목표
- **OOP 설계:** `GameManager`와 `Entity` 클래스 분리를 통한 역할과 책임의 명확화
- **메모리 관리:** 포인터와 동적 할당(`new`/`delete`)을 활용한 적(Enemy) 오브젝트 관리
- **자료 구조:** `std::vector`를 활용한 가변적인 게임 오브젝트 관리
- **알고리즘:** 좌표 기반의 충돌 감지 및 턴제 전투 로직 구현

## 🎮 주요 기능
1. **플레이어 조작**: WASD 키를 이용한 실시간 이동 시스템
2. **전투 시스템**: 적과 조우 시 자동으로 발생하는 턴제 기반 공격 및 피격 로직
3. **상태창 UI**: HP, 공격력, 전투 로그(Log) 실시간 텍스트 렌더링
4. **승리/패배 조건**: 탈출구(X) 도달 시 승리, HP 0 소진 시 패배

## 🛠 기술 스택 (Tech Stack)
- **Language**: C++ 14
- **Environment**: Visual Studio (Windows Console)
- **Key Concepts**: OOP, Game Loop, Dynamic Allocation, STL Container

## 📂 프로젝트 구조
```text
src/
├── Entity.h/cpp      # Player 및 Monster 객체 속성 및 행동 정의
├── GameManager.h/cpp # 게임 루프, 맵 렌더링, 입력 처리, 충돌 로직 담당
└── main.cpp          # 프로그램 진입점 (Entry Point)
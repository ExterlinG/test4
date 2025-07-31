#pragma once
#include <vector>
#include "Planet.h"  // �T�q�u�t�y���u����, ������ �������� �����p�r�y�|���~���z
#include "Ship.h"
#include "Player.h"
#include "AI.h"
class Game {
public:
    Game();
    void Run();  // �C�|�p�r�~���z �y�s�����r���z ���y�{�|
    void HandleInput();
    void Initialize();
    void Cleanup();
    bool ShouldQuit() const;
    void Update()
    {
        enemyAI.Update();
    }
    void Render();
    Player player;
    AI enemyAI;
    Game() : enemyAI(this) {} // �P�u���u�t�p�u�} �������|�{�� �~�p �y�s����
    std::vector<Ship> activeShips;
    void SendShips(Planet* source, Planet* target, int count, int owner);
    void HandleGlobalInput() {
        player.HandleInput(planets);
    }

private:
    std::vector<Planet> planets;
    bool isRunning;
    // �D���q�p�r�����u �t�����s�y�u �y�s�����r���u �������������~�y�� ���� �~�u���q�����t�y�}�������y
};

struct VectorI2
{
    int x, y;
};

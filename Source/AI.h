#pragma once
#include "Game.h"
#include "Planet.h"
#include "Ship.h"
#include <vector>
#include <algorithm>

class AI {
public:
    AI(Game* gameRef);

    void Update(); // �O���~���r�~���z �}�u�����t ���q�~���r�|�u�~�y��
    void MakeStrategicDecision(); // �P���y�~�����y�u ���u���u�~�y�z
    void LaunchAttack(); // �@���p�{�p �~�p �y�s�����{�p

private:
    Game* game;
    int difficultyLevel = 1; // 1-3: �|�u�s�{�y�z-���|���w�~���z
    float lastActionTime = 0;

    // �B�������}���s�p���u�|���~���u �}�u�����t��
    Planet* FindWeakestPlayerPlanet();
    Planet* FindStrongestAIPlanet();
    bool ShouldLaunchAttack() const;
    int CalculateRequiredShips(const Planet& target) const;
};
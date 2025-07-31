#pragma once
#include "DxLib.h"
#include "Planet.h" // �D�|�� ���p�q������ �� ���|�p�~�u���p�}�y

class Ship {
public:
    Ship(int owner, Planet* source, Planet* target, int count);

    void Update(); // �O�q�~���r�|�u�~�y�u �����x�y���y�y
    void Draw() const; // �O�����y�����r�{�p �{�����p�q�|��
    bool HasArrived() const; // �P�����r�u���{�p �����y�q�����y��

    // �C�u�����u����
    int GetOwner() const { return owner; }
    float GetProgress() const { return progress; }

private:
    int owner; // �B�|�p�t�u�|�u�� (PLAYER/ENEMY)
    int shipCount; // �K���|�y���u�����r�� �{�����p�q�|�u�z �r �s���������u
    float progress; // �P�����s���u���� ���u���u�}�u���u�~�y�� (0..1)

    // �P�|�p�~�u���� �}�p�����������p
    Planet* sourcePlanet;
    Planet* targetPlanet;

    // �S�u�{�����y�u �{�������t�y�~�p����
    float currentX;
    float currentY;

    // �C���p���y�{�p
    int shipImage; // �I�x���q���p�w�u�~�y�u �{�����p�q�|��
};

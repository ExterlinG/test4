#include "Planet.h"

Planet::Planet(float x, float y, float radius, Owner owner,
    int resources, int image, int id)
    : x(x), y(y), radius(radius), owner(owner),
    resources(resources), groundImage(image), planetId(id)
{
    SetOwner(owner); // �I�~�y���y�p�|�y�x�p���y�� ���r�u���p
}

void Planet::SetOwner(Owner newOwner) {
    owner = newOwner;
    switch (owner) {
    case Owner::PLAYER:
        color = GetColor(255, 0, 0); // �K���p���~���z
        break;
    case Owner::ENEMY:
        color = GetColor(255, 255, 0); // �G�v�|�����z
        break;
    default:
        color = GetColor(128, 128, 128); // �R�u�����z
    }
}

void Planet::Draw() const {
    // �@�~�y�}�y�����r�p�~�~�p�� �������y�����r�{�p (�{�p�{ �r �r�p���u�} �{���t�u)
    DrawCircle(x + radius, y + radius, radius, color, FALSE, 5.0f);
    // �D���q�p�r�����u �x�t�u���� DrawGraph �t�|�� �p�~�y�}�p���y�y, �u���|�y �~���w�~��
}
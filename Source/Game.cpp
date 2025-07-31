#include "Game.h"
#include "Render.h"  // �D�|�� �������y�����r�{�y
#include "DxLib.h"          // �D�|�� �����~�{���y�z DxLib
#include "Ship.h"
Game::Game() : isRunning(true) {
    // �I�~�y���y�p�|�y�x�p���y�� ���|�p�~�u�� (���u���u�~�u���y���u �{���t �y�x playScene.cpp)
    Render::Initialize();

    Planet planets[PLANET_MAX] =
    {

            Planet(689,128, PLANET_CENTER, Planet::Owner::PLAYER, 200, -1,-1),
            Planet(848, 96, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
            Planet(1008, 128, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
            Planet(1136, 224, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
            Planet(1192, 368, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
            Planet(1096, 509, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
            Planet(1456, 428, PLANET_CENTER, Planet::Owner::ENEMY, 200, -1,-1),
            Planet(1408, 592, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
            Planet(1280, 720, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
            Planet(1104, 768, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
            Planet(944, 704, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
            Planet(848, 560, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
            Planet(848.5, 911, PLANET_CENTER, Planet::Owner::ENEMY, 200, -1,-1),
            Planet(704, 800, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
            Planet(624, 640, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
            Planet(655, 464, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
            Planet(785, 352, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
            Planet(960, 336, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
            Planet(960,476, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),


    };
    const VectorI2 defaultPos[PLANET_MAX] = {
    {689,128},{848, 96},{1008, 128},
    {1136, 224},{1192, 368},{1096, 509},
    {1456, 428},{1408, 592},{1280, 720},
    {1104, 768},{944, 704},{848, 560},
    {848.5, 911},{704, 800},{624, 640},
    {655, 464},{785, 352},{960, 336},{960,476}
    };

    for (int i = 0; i < PLANET_MAX; i++) {
        planets.emplace_back(
            defaultPos[i].x,
            defaultPos[i].y,
            PLANET_RADIUS,
            Owner::NEUTRAL
        );
    }
}

void Game::Run() {
    while (isRunning && ProcessMessage() == 0) {
        HandleInput();
        Update();
        Render();
        WaitTimer(16);  // ~60 FPS
    }
}

void Game::HandleInput() {
    // �P�u���u�~�u���y���u �����t�p ���q���p�q�����{�� �r�r���t�p �y�x playScene.cpp
    for (int i = 0; i < PLANET_MAX; i++) {
        planets[i] = Planet(
            defaultPos[i].x,      // �R���p���y���~�p�� X-�{�������t�y�~�p���p
            defaultPos[i].y,      // �R���p���y���~�p�� Y-�{�������t�y�~�p���p
            PLANET_RADIUS,        // �Q�p�t�y����
            Owner::NEUTRAL,       // �B�|�p�t�u�|�u��
            200,                  // �Q�u����������
            groundImage,          // �S�u�{���������p
            i                     // ID ���|�p�~�u����
        );
    }
}

void Game::Update() {
    // �L���s�y�{�p ���q�~���r�|�u�~�y�� ���|�p�~�u��/�{�����p�q�|�u�z
      // �O�q�~���r�|�u�~�y�u �{�����p�q�|�u�z
    // �O�q�~���r�|�u�~�y�u �{�����p�q�|�u�z
    for (auto& ship : activeShips) {
        ship.Update();
        if (ship.HasArrived()) {
            // �L���s�y�{�p �����y�q�����y��
            Planet* target = /* �����|�����p�u�} ���u�|�u�r���� ���|�p�~�u���� */;
            target->SetOwner(ship.GetOwner());
        }
    }

    // �T�t�p�|�u�~�y�u �����y�q���r���y�� �{�����p�q�|�u�z
    activeShips.erase(
        std::remove_if(activeShips.begin(), activeShips.end(),
            [](const Ship& s) { return s.HasArrived(); }),
        activeShips.end());

    HandleGlobalInput();
    Update();
    Render::UpdateAnimations();
}

void Game::SendShips(Planet* source, Planet* target, int count, int owner) {
    if (source->GetOwner() == owner && source->resources >= count) {
        activeShips.emplace_back(owner, source, target, count);
        source->resources -= count;
    }
}


void Game::Render() {
    ClearDrawScreen();  // �O���y�����{�p ���{���p�~�p
    for (auto& connection : planetConnections) {
        Render::DrawConnection(planets[connection.from], planets[connection.to],
            GetColor(100, 100, 100));
    }
    for (auto& planet : planets) {
        Render::DrawPlanet(planet);  // �O�����y�����r�{�p ���u���u�x Systems/Render
    }
    for (auto& ship : activeShips) {
        Render::DrawShip(ship);
    }

    ScreenFlip();  // �O�q�~���r�|�u�~�y�u ���{���p�~�p
}
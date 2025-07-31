#include "Game.h"
#include "Render.h"  // �D�|�� �������y�����r�{�y
#include "DxLib.h"          // �D�|�� �����~�{���y�z DxLib
#include "Ship.h"
Game::Game() : isRunning(true), ai(this) {
    // �I�~�y���y�p�|�y�x�p���y�� �y�s�����{�p
    player = Player(Owner::PLAYER);
}

void Game::Initialize() {
    // 1. �I�~�y���y�p�|�y�x�p���y�� ���|�p�~�u�� (�����y�}�u�� �t�|�� 5 ���|�p�~�u��)
    constexpr int PLANET_COUNT = 5;
    planets.reserve(PLANET_COUNT);

    for (int i = 0; i < PLANET_COUNT; ++i) {
        planets.emplace_back(
            static_cast<float>(100 + i * 200), // x
            static_cast<float>(300),            // y
            40.0f,                             // radius
            (i == 0) ? Owner::PLAYER :         // �P�u���r�p�� ���|�p�~�u���p - �y�s�����{�p
            (i == 1) ? Owner::ENEMY :          // �B�������p�� - �r���p�s�p
            Owner::NEUTRAL,                    // �O�����p�|���~���u �~�u�z�����p�|���~���u
            200,                               // ���u����������
            0,                                 // imageId (�x�p�}�u�~�y���u �~�p ���u�p�|���~���z)
            i                                  // planetId
        );
    }

    // 2. �I�~�y���y�p�|�y�x�p���y�� ���y�����u�}
    Render::Initialize();
    ai.Initialize();
}

void Game::HandleInput() {
    player.HandleInput(planets); // �O���u���p���{�p �y�������p�r�|�u�~�p: planets -> planets
}

void Game::Update(float deltaTime) {
    // 1. �O�q�~���r�|�u�~�y�u �{�����p�q�|�u�z
    for (auto& ship : ships) {
        ship.Update(deltaTime);
    }

    // 2. �P�����r�u���{�p �{���|�|�y�x�y�z
    CheckCollisions();

    // 3. �O�q�~���r�|�u�~�y�u �I�I
    ai.Update();
}

void Game::Render() {
    Render::BeginFrame();

    // 1. �O�����y�����r�{�p ���|�p�~�u��
    for (const auto& planet : planets) {
        Render::DrawPlanet(planet);
    }

    // 2. �O�����y�����r�{�p �{�����p�q�|�u�z
    for (const auto& ship : ships) {
        Render::DrawShip(ship);
    }

    Render::EndFrame();
}

void Game::CreateShip(Planet* source, Planet* target, int count, Owner owner) {
    ships.emplace_back(owner, source, target, count);
}
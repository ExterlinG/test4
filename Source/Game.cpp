#include "Game.h"
#include "Render.h"  // ÑDÑ|Ñë ÑÄÑÑÑÇÑyÑÉÑÄÑrÑ{Ñy
#include "DxLib.h"          // ÑDÑ|Ñë ÑÜÑÖÑ~Ñ{ÑàÑyÑz DxLib
#include "Ship.h"
Game::Game() : isRunning(true) {
    // ÑIÑ~ÑyÑàÑyÑpÑ|ÑyÑxÑpÑàÑyÑë ÑÅÑ|ÑpÑ~ÑuÑÑ (ÑÅÑuÑÇÑuÑ~ÑuÑÉÑyÑÑÑu Ñ{ÑÄÑt ÑyÑx playScene.cpp)
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
    // ÑPÑuÑÇÑuÑ~ÑuÑÉÑyÑÑÑu ÑÉÑêÑtÑp ÑÄÑqÑÇÑpÑqÑÄÑÑÑ{ÑÖ ÑrÑrÑÄÑtÑp ÑyÑx playScene.cpp
    for (int i = 0; i < PLANET_MAX; i++) {
        planets[i] = Planet(
            defaultPos[i].x,      // ÑRÑÑÑpÑÑÑyÑâÑ~ÑpÑë X-Ñ{ÑÄÑÄÑÇÑtÑyÑ~ÑpÑÑÑp
            defaultPos[i].y,      // ÑRÑÑÑpÑÑÑyÑâÑ~ÑpÑë Y-Ñ{ÑÄÑÄÑÇÑtÑyÑ~ÑpÑÑÑp
            PLANET_RADIUS,        // ÑQÑpÑtÑyÑÖÑÉ
            Owner::NEUTRAL,       // ÑBÑ|ÑpÑtÑuÑ|ÑuÑà
            200,                  // ÑQÑuÑÉÑÖÑÇÑÉÑç
            groundImage,          // ÑSÑuÑ{ÑÉÑÑÑÖÑÇÑp
            i                     // ID ÑÅÑ|ÑpÑ~ÑuÑÑÑç
        );
    }
}

void Game::Update() {
    // ÑLÑÄÑsÑyÑ{Ñp ÑÄÑqÑ~ÑÄÑrÑ|ÑuÑ~ÑyÑë ÑÅÑ|ÑpÑ~ÑuÑÑ/Ñ{ÑÄÑÇÑpÑqÑ|ÑuÑz
      // ÑOÑqÑ~ÑÄÑrÑ|ÑuÑ~ÑyÑu Ñ{ÑÄÑÇÑpÑqÑ|ÑuÑz
    // ÑOÑqÑ~ÑÄÑrÑ|ÑuÑ~ÑyÑu Ñ{ÑÄÑÇÑpÑqÑ|ÑuÑz
    for (auto& ship : activeShips) {
        ship.Update();
        if (ship.HasArrived()) {
            // ÑLÑÄÑsÑyÑ{Ñp ÑÅÑÇÑyÑqÑçÑÑÑyÑë
            Planet* target = /* ÑÅÑÄÑ|ÑÖÑâÑpÑuÑ} ÑàÑuÑ|ÑuÑrÑÖÑê ÑÅÑ|ÑpÑ~ÑuÑÑÑÖ */;
            target->SetOwner(ship.GetOwner());
        }
    }

    // ÑTÑtÑpÑ|ÑuÑ~ÑyÑu ÑÅÑÇÑyÑqÑçÑrÑäÑyÑá Ñ{ÑÄÑÇÑpÑqÑ|ÑuÑz
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
    ClearDrawScreen();  // ÑOÑâÑyÑÉÑÑÑ{Ñp ÑèÑ{ÑÇÑpÑ~Ñp
    for (auto& connection : planetConnections) {
        Render::DrawConnection(planets[connection.from], planets[connection.to],
            GetColor(100, 100, 100));
    }
    for (auto& planet : planets) {
        Render::DrawPlanet(planet);  // ÑOÑÑÑÇÑyÑÉÑÄÑrÑ{Ñp ÑâÑuÑÇÑuÑx Systems/Render
    }
    for (auto& ship : activeShips) {
        Render::DrawShip(ship);
    }

    ScreenFlip();  // ÑOÑqÑ~ÑÄÑrÑ|ÑuÑ~ÑyÑu ÑèÑ{ÑÇÑpÑ~Ñp
}
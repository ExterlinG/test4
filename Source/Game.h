#pragma once
#include <vector>
#include "Planet.h"  // „T„q„u„t„y„„„u„ƒ„, „‰„„„€ „„…„„„ „„‚„p„r„y„|„„~„„z
#include "Ship.h"
#include "Player.h"
#include "AI.h"
class Game {
public:
    Game();
    void Run();  // „C„|„p„r„~„„z „y„s„‚„€„r„€„z „ˆ„y„{„|
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
    Game() : enemyAI(this) {} // „P„u„‚„u„t„p„u„} „ƒ„ƒ„„|„{„… „~„p „y„s„‚„…
    std::vector<Ship> activeShips;
    void SendShips(Planet* source, Planet* target, int count, int owner);
    void HandleGlobalInput() {
        player.HandleInput(planets);
    }

private:
    std::vector<Planet> planets;
    bool isRunning;
    // „D„€„q„p„r„„„„u „t„‚„…„s„y„u „y„s„‚„€„r„„u „ƒ„€„ƒ„„„€„‘„~„y„‘ „„€ „~„u„€„q„‡„€„t„y„}„€„ƒ„„„y
};

struct VectorI2
{
    int x, y;
};

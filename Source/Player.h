#pragma once
#include "Planet.h"
#include "Ship.h"
#include <vector>

class Player {
public:
    Player(int id);

    void HandleInput(const std::vector<Planet>& planets);
    void Update();
    void SendFleet(Planet* source, Planet* target);

    // „R„€„ƒ„„„€„‘„~„y„u „y„s„‚„€„{„p
    int GetResources() const { return totalResources; }
    int GetSelectedPlanetId() const { return selectedPlanetId; }

private:
    int playerId;
    int totalResources;
    int selectedPlanetId = -1; // -1 „€„x„~„p„‰„p„u„„ „~„y„‰„u„s„€ „~„u „r„„q„‚„p„~„€

    // „S„p„z„}„y„~„s„y „t„|„‘ „…„„‚„p„r„|„u„~„y„‘
    int lastClickTime = 0;
    const int clickDelay = 200; // „H„p„t„u„‚„w„{„p „}„u„w„t„… „{„|„y„{„p„}„y „r „}„ƒ

    bool IsDoubleClick() const;
    Planet* GetPlanetById(int id, std::vector<Planet>& planets);
};

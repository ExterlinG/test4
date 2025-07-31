#include "AI.h"
#include "DxLib.h" // „D„|„‘ GetNowCount()

AI::AI(Game* gameRef) : game(gameRef) {}

void AI::Update() {
    float currentTime = GetNowCount() / 1000.0f; // „B „ƒ„u„{„…„~„t„p„‡

    // „P„‚„€„r„u„‚„‘„u„} „r„‚„u„}„‘ „„€„ƒ„|„u„t„~„u„s„€ „t„u„z„ƒ„„„r„y„‘
    if (currentTime - lastActionTime > (4.0f / difficultyLevel)) {
        MakeStrategicDecision();
        lastActionTime = currentTime;
    }
}

void AI::MakeStrategicDecision() {
    if (ShouldLaunchAttack()) {
        LaunchAttack();
    }
    // „M„€„w„~„€ „t„€„q„p„r„y„„„ „t„‚„…„s„y„u „ƒ„„„‚„p„„„u„s„y„‰„u„ƒ„{„y„u „‚„u„Š„u„~„y„‘
}

void AI::LaunchAttack() {
    Planet* target = FindWeakestPlayerPlanet();
    Planet* source = FindStrongestAIPlanet();

    if (target && source && source->resources > 10) {
        int shipsToSend = std::min(
            source->resources / 2,
            CalculateRequiredShips(*target)
        );

        // „R„€„x„t„p„u„} „{„€„‚„p„q„|„ „‰„u„‚„u„x „y„s„‚„€„r„€„z „}„u„~„u„t„w„u„‚
        game->CreateShip(source, target, shipsToSend, Owner::ENEMY);
        source->resources -= shipsToSend;
    }
}

// „B„ƒ„„€„}„€„s„p„„„u„|„„~„„u „}„u„„„€„t„
Planet* AI::FindWeakestPlayerPlanet() {
    Planet* weakest = nullptr;
    for (auto& planet : game->GetPlanets()) {
        if (planet.GetOwner() == Owner::PLAYER) {
            if (!weakest || planet.resources < weakest->resources) {
                weakest = &planet;
            }
        }
    }
    return weakest;
}

Planet* AI::FindStrongestAIPlanet() {
    Planet* strongest = nullptr;
    for (auto& planet : game->GetPlanets()) {
        if (planet.GetOwner() == Owner::ENEMY) {
            if (!strongest || planet.resources > strongest->resources) {
                strongest = &planet;
            }
        }
    }
    return strongest;
}

bool AI::ShouldLaunchAttack() const {
    // „P„‚„€„ƒ„„„p„‘ „|„€„s„y„{„p - „p„„„p„{„…„u„} „ƒ 70% „r„u„‚„€„‘„„„~„€„ƒ„„„„
    return (rand() % 100) < 70;
}

int AI::CalculateRequiredShips(const Planet& target) const {
    // „A„u„‚„u„} „~„p 20% „q„€„|„„Š„u „‰„u„} „x„p„‹„y„„„~„y„{„€„r
    return target.resources * 1.2f;
}
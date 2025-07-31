#include "Player.h"
#include "DxLib.h" // „D„|„‘ GetNowCount()

Player::Player(int id) : playerId(id), totalResources(1000) {}

void Player::HandleInput(const std::vector<Planet>& planets) {
    if (GetMouseInput() & MOUSE_INPUT_LEFT) {
        int currentTime = GetNowCount();

        // „P„‚„€„r„u„‚„‘„u„} „t„r„€„z„~„€„z „{„|„y„{
        if (currentTime - lastClickTime < clickDelay) {
            int mouseX, mouseY;
            GetMousePoint(&mouseX, &mouseY);

            for (auto& planet : planets) {
                if (CheckCollisionPointCircle(mouseX, mouseY, planet.x, planet.y, planet.radius)) {
                    if (selectedPlanetId == -1) {
                        selectedPlanetId = planet.planetId;
                    }
                    else if (selectedPlanetId != planet.planetId) {
                        // „O„„„„‚„p„r„{„p „†„|„€„„„p „}„u„w„t„… „„|„p„~„u„„„p„}„y
                        Planet* source = GetPlanetById(selectedPlanetId, planets);
                        Planet* target = GetPlanetById(planet.planetId, planets);
                        if (source && target) {
                            SendFleet(source, target);
                        }
                        selectedPlanetId = -1;
                    }
                    break;
                }
            }
        }
        lastClickTime = currentTime;
    }
}

void Player::SendFleet(Planet* source, Planet* target) {
    if (source->GetOwner() == playerId && source->resources > 10) {
        int shipsToSend = source->resources / 2;
        // „R„€„x„t„p„~„y„u „{„€„‚„p„q„|„‘ „q„…„t„u„„ „€„q„‚„p„q„p„„„„r„p„„„„ƒ„‘ „r Game
        source->resources -= shipsToSend;
        // „H„t„u„ƒ„ „t„€„|„w„u„~ „q„„„„ „r„„x„€„r game.CreateShip()
    }
}

// „B„ƒ„„€„}„€„s„p„„„u„|„„~„„u „†„…„~„{„ˆ„y„y
bool Player::IsDoubleClick() const {
    return (GetNowCount() - lastClickTime) < clickDelay;
}

Planet* Player::GetPlanetById(int id, std::vector<Planet>& planets) {
    for (auto& planet : planets) {
        if (planet.planetId == id) return &planet;
    }
    return nullptr;
}
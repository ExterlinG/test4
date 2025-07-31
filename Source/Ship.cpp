#include "Ship.h"

Ship::Ship(int owner, Planet* source, Planet* target, int count)
    : owner(owner), sourcePlanet(source), targetPlanet(target),
    shipCount(count), progress(0.0f)
{
    // „I„~„y„ˆ„y„p„|„y„x„p„ˆ„y„‘ „„€„x„y„ˆ„y„y
    currentX = source->x + source->radius;
    currentY = source->y + source->radius;

    // „H„p„s„‚„…„x„{„p „y„x„€„q„‚„p„w„u„~„y„‘ („„‚„y„}„u„‚ „t„|„‘ DxLib)
    shipImage = LoadGraph("data/ship.png");
}

void Ship::Update() {
    if (progress >= 1.0f) return;

    progress += 0.005f; // „R„{„€„‚„€„ƒ„„„Ž „„u„‚„u„}„u„‹„u„~„y„‘

    // „L„y„~„u„z„~„p„‘ „y„~„„„u„‚„„€„|„‘„ˆ„y„‘ „„€„x„y„ˆ„y„y
    currentX = sourcePlanet->x + (targetPlanet->x - sourcePlanet->x) * progress;
    currentY = sourcePlanet->y + (targetPlanet->y - sourcePlanet->y) * progress;
}

void Ship::Draw() const {
    int drawColor = (owner == 1) ? GetColor(255, 0, 0) : GetColor(255, 255, 0);

    // „O„„„‚„y„ƒ„€„r„{„p „{„€„‚„p„q„|„‘
    DrawCircle(currentX, currentY, 10, drawColor, TRUE);

    // „I„|„y „‰„u„‚„u„x „y„x„€„q„‚„p„w„u„~„y„u:
    // DrawRotaGraph(currentX, currentY, 1.0, 0, shipImage, TRUE);

    // „O„„„‚„y„ƒ„€„r„{„p „{„€„|„y„‰„u„ƒ„„„r„p „{„€„‚„p„q„|„u„z
    DrawFormatString(currentX + 15, currentY - 5, GetColor(255, 255, 255), "%d", shipCount);
}

bool Ship::HasArrived() const {
    return progress >= 1.0f;
}
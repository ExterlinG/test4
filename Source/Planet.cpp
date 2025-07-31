#include "Planet.h"

Planet::Planet(float x, float y, float radius, Owner owner,
    int resources, int image, int id)
    : x(x), y(y), radius(radius), owner(owner),
    resources(resources), groundImage(image), planetId(id)
{
    SetOwner(owner); // „I„~„y„ˆ„y„p„|„y„x„p„ˆ„y„‘ „ˆ„r„u„„„p
}

void Planet::SetOwner(Owner newOwner) {
    owner = newOwner;
    switch (owner) {
    case Owner::PLAYER:
        color = GetColor(255, 0, 0); // „K„‚„p„ƒ„~„„z
        break;
    case Owner::ENEMY:
        color = GetColor(255, 255, 0); // „G„v„|„„„„z
        break;
    default:
        color = GetColor(128, 128, 128); // „R„u„‚„„z
    }
}

void Planet::Draw() const {
    // „@„~„y„}„y„‚„€„r„p„~„~„p„‘ „€„„„‚„y„ƒ„€„r„{„p („{„p„{ „r „r„p„Š„u„} „{„€„t„u)
    DrawCircle(x + radius, y + radius, radius, color, FALSE, 5.0f);
    // „D„€„q„p„r„„„„u „x„t„u„ƒ„ DrawGraph „t„|„‘ „p„~„y„}„p„ˆ„y„y, „u„ƒ„|„y „~„…„w„~„€
}
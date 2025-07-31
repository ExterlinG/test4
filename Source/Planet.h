#pragma once
#include "DxLib.h"

enum class Owner {
    NEUTRAL,
    PLAYER,
    ENEMY
};

class Planet {
public:
    // „R„„„p„„„y„‰„~„„u „{„€„€„‚„t„y„~„p„„„ („{„p„{ „r „r„p„Š„u„} „{„€„t„u)
    float x, y;
    float radius;
    int resources;
    int planetId;
    int groundImage; // „D„|„‘ „p„~„y„}„p„ˆ„y„y

    Planet(float x, float y, float radius, Owner owner, int resources, int image, int id);

    void SetOwner(Owner newOwner);
    void Draw() const;

    Owner GetOwner() const { return owner; }
    int GetColor() const { return color; }

private:
    Owner owner;
    int color; // „W„r„u„„ „„|„p„~„u„„„
};
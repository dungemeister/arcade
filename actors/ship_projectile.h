#pragma once
#include "projectile.h"

class ShipProjectile: public Projectile
{
public:
    ShipProjectile(Game* game, const std::string& sprite_filename);
    void UpdateActor(float deltatime) override;
};
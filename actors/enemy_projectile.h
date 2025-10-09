#pragma once
#include "projectile.h"

class EnemyProjectile: public Projectile{
public:    
    EnemyProjectile(Game* game, const std::string& sprite_filename);
    void UpdateActor(float deltatime) override;
};
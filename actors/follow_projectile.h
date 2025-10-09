#pragma once
#include "actor.hpp"
#include "sprite_component.h"
#include "follow_move_component.h"
#include <string>

class FollowProjectile: public Actor{
public:
    FollowProjectile(Game* game, const std::string& sprite_filename);

    void UpdateActor(float deltatime) override;
    void SetProjectileAngularSpeed(float val);
    void SetProjectileForwardSpeed(float val);
    void SetTargetPosition(const Vector2& vec);
private:
    SpriteComponent *m_sc;
    FollowMC *m_fmc;
};
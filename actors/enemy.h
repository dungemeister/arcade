#pragma once
#include "actor.hpp"
#include "types.h"
#include "follow_move_component.h"
#include "circle_component.h"
#include <string>

class Enemy: public Actor{
public:
    Enemy(Game* game, const std::string& sprite_filename);
    ~Enemy();

    void UpdateActor(float deltatime) override;
    CircleComponent* GetCircleComponent() { return m_circle; }

private:
    Vector2 m_ship_position;
    FollowMC* m_fmc;
    CircleComponent* m_circle;
    float m_shoot_cooldown_time;
    float m_shoot_cooldown_period;
};
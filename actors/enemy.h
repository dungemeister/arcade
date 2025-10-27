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

    static int GetEnemiesAmount() { return m_amount; }
    void SetMoveStrategy(MoveComponent* component) { m_fmc = component; }
private:
    Vector2 m_ship_position;
    MoveComponent* m_fmc;
    CircleComponent* m_circle;
    float m_shoot_cooldown_time;
    float m_shoot_cooldown_period;
    static int m_amount;
};
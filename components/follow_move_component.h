#pragma once
#include "move_component.h"
#include "actor.hpp"

class FollowMC: public MoveComponent
{
public:
    FollowMC(Actor* owner, int update_order);
    void Update(float deltatime) override;
    void SetTargetPos(const Vector2& pos) { m_target_pos = pos; }
    void SetHorizontalBorder(float x) { m_hor_border = x; }
    void SetVerticalBorder(float y) { m_ver_border = y; }
private:
    Vector2 m_target_pos;
    float m_hor_border;
    float m_ver_border;
};
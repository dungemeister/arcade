#pragma once
#include "sprite_component.h"
#include "actor.hpp"

class CircleComponent: public Component{
public:
    CircleComponent(Actor* owner, int update_order);
    void SetRadius(float radius) { m_radius = radius; }
    float GetRadius() const { return m_radius * m_owner->GetScale(); }
    const Vector2& GetCenter() const { return m_owner->GetPosition(); }
private:
    float m_radius;
};

static bool CirclesIntersect(const CircleComponent& a, const CircleComponent& b){
    auto diff = a.GetCenter() - b.GetCenter();
    auto distance_sq = diff.getLengthSquared();

    auto mark = a.GetRadius() + b.GetRadius();

    return distance_sq <= mark * mark;
}

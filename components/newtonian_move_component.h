#pragma once
#include "move_component.h"
#include "types.h"

class NewtonianMoveComponent: public MoveComponent{
public:
    NewtonianMoveComponent(Actor* owner, int update_order);
    void AddForce(const Vector2& force);
    void Update(float deltatime) override;
    void SetPosition(const Vector2& pos) { m_position = pos; }
    void SetMass(float mass) { m_mass = mass; }
private:
    float m_mass;
    Vector2 m_force;
    Vector2 m_position;
    Vector2 m_velocity;
    Vector2 m_acceleration;
    void CalculateParams(float deltatime);
    void PositionCorrection();
};
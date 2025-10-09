#include "newtonian_move_component.h"
#include "game.h"

NewtonianMoveComponent::NewtonianMoveComponent(Actor* owner, int update_order)
    :MoveComponent(owner, update_order)
    ,m_force()
    ,m_position()
    ,m_velocity()
    ,m_acceleration()
    ,m_mass(0.f)
{
    
}

void NewtonianMoveComponent::AddForce(const Vector2& force){
    m_force += force;
    if(m_force.x > 200.f)  m_force.x = 200.f;
    if(m_force.y > 200.f)  m_force.y = 200.f;

    if(m_force.x < -200.f)  m_force.x = -200.f;
    if(m_force.y < -200.f)  m_force.y = -200.f;
}

void NewtonianMoveComponent::Update(float deltatime){
    CalculateParams(deltatime);

    PositionCorrection();
    m_owner->SetPosition(m_position);
}

void NewtonianMoveComponent::PositionCorrection(){
    auto pos = m_position;
    if (pos.x < 0.0f) { pos.x = m_owner->GetGame()->GetWindowWidth() - 2.0f; }
    else if (pos.x > m_owner->GetGame()->GetWindowWidth()) { pos.x = 2.0f; }

    if (pos.y < 0.0f) { pos.y = m_owner->GetGame()->GetWindowHeight() - 2.0f; }
    else if (pos.y > m_owner->GetGame()->GetWindowHeight()) { pos.y = 2.0f; }
    m_position = pos;
}

void NewtonianMoveComponent::CalculateParams(float deltatime){
    m_acceleration = m_force / m_mass;

    m_velocity += m_acceleration * deltatime;
    m_position += m_velocity * deltatime;

    if(m_velocity.x > 0.f){
        m_force.x -= 5.f;
        if(m_force.x < 0) m_force.x = 0.f;
    }
    if(m_velocity.x < 0.f){
        m_force.x += 5.f;
        if(m_force.x > 0) m_force.x = 0.f;
    }
}
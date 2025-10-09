#include "input_component.h"
#include "game.h"

InputComponent::InputComponent(Actor* owner, int update_order)
    :MoveComponent(owner, update_order),
    m_max_forward_speed(0),
    m_max_angular_speed(0),
    m_forward_key(0),
    m_back_key(0),
    m_clockwise_key(0),
    m_counter_clockwise_key(0)
{

}

void InputComponent::ProcessInput(const bool* state){
    float forward_speed = 0.f;
    float angular_speed = 0.f;

    if(state[m_forward_key]){
        forward_speed += m_max_forward_speed;
        // AddForce({200.f, 0.f});
    }

    if(state[m_back_key]){
        forward_speed -= m_max_forward_speed;
        // AddForce({-200.f, 0.f});
    }
    SetForwardSpeed(forward_speed);

    if(state[m_clockwise_key]){
        angular_speed += m_max_angular_speed;
    }
    if(state[m_counter_clockwise_key]){
        angular_speed -= m_max_angular_speed;
    }
    SetAngularSpeed(angular_speed);
}

void InputComponent::Update(float deltatime){
    // NewtonianMoveComponent::Update(deltatime);
    // return;
    if(GetAngularSpeed() != 0){
        float rot = m_owner->GetRotation();
		rot += GetAngularSpeed() * deltatime;
		m_owner->SetRotation(rot);
        // std::cout << "rotation:" << m_owner->GetRotation() << " ";

    }
    if(GetForwardSpeed() != 0){
        auto pos = m_owner->GetPosition();
        pos += m_owner->GetForward() * GetForwardSpeed() * deltatime;

        if (pos.x < 0.0f) { pos.x = m_owner->GetGame()->GetWindowWidth() - 2.0f; }
		else if (pos.x > m_owner->GetGame()->GetWindowWidth()) { pos.x = 2.0f; }

		if (pos.y < 0.0f) { pos.y = m_owner->GetGame()->GetWindowHeight() - 2.0f; }
		else if (pos.y > m_owner->GetGame()->GetWindowHeight()) { pos.y = 2.0f; }

		m_owner->SetPosition(pos);
        // std::cout << "x: " << m_owner->GetPosition().x << " y: " << m_owner->GetPosition().y << "\n";
    }
}
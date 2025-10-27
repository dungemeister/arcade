#include "input_component.h"
#include "game.h"

InputComponent::InputComponent(Actor* owner, int update_order)
    :MoveComponent(owner, update_order),
    m_max_forward_speed(0),
    m_max_vertical_speed(0),
    m_forward_key(0),
    m_back_key(0),
    m_up_key(0),
    m_down_key(0)
{

}

void InputComponent::ProcessInput(const bool* state){
    float forward_speed = 0.f;
    float vertical_speed = 0.f;

    if(state[m_forward_key]){
        forward_speed += m_max_forward_speed;
        // AddForce({200.f, 0.f});
    }

    if(state[m_back_key]){
        forward_speed -= m_max_forward_speed;
        // AddForce({-200.f, 0.f});
    }
    SetForwardSpeed(forward_speed);

    if(state[m_down_key]){
        vertical_speed += m_max_vertical_speed;
    }
    if(state[m_up_key]){
        vertical_speed -= m_max_vertical_speed;
    }
    SetVerticalSpeed(vertical_speed);
}

void InputComponent::Update(float deltatime){
    if(GetAngularSpeed() != 0){
        float rot = m_owner->GetRotation();
		rot += GetAngularSpeed() * deltatime;
		m_owner->SetRotation(rot);

    }
    if(GetVerticalSpeed() != 0){
        auto pos = m_owner->GetPosition();
        pos.y += GetVerticalSpeed() * deltatime;
        float vert_up_border = 0.f;
        float vert_down_border = m_owner->GetGame()->GetWindowHeight();
        if (pos.y < vert_up_border) { pos.y = vert_up_border - 2.0f; }
        if (pos.y > vert_down_border) { pos.y = vert_down_border - 2.0f; }
        m_owner->SetPosition(pos);
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
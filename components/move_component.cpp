#include "move_component.h"
#include "game.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
    :Component(owner, updateOrder)
    ,m_angular_speed(0.f)
    ,m_forward_speed(0.f)
{

}

void MoveComponent::Update(float deltatime){
    // std::cout << "[" << this << "] "; 
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
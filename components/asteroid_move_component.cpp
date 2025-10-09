#include "asteroid_move_component.h"
#include "game.h"
#include <iostream>

AsteroidMC::AsteroidMC(Actor* owner, int update_order)
    :MoveComponent(owner, update_order)
{

}

void AsteroidMC::Update(float deltatime){
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
        float radius = 10.f;
        if (pos.x + radius < 0.0f) { pos.x = m_owner->GetGame()->GetWindowWidth() - radius; }
		else if (pos.x - radius > m_owner->GetGame()->GetWindowWidth()) { pos.x = -radius; }

		if (pos.y < 0.0f) { pos.y = m_owner->GetGame()->GetWindowHeight() - 2.0f; }
		else if (pos.y > m_owner->GetGame()->GetWindowHeight()) { pos.y = 2.0f; }

		m_owner->SetPosition(pos);
        // std::cout << "x: " << m_owner->GetPosition().x << " y: " << m_owner->GetPosition().y << "\n";
    }
}
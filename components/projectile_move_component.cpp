#include "projectile_move_component.h"

ProjectileMC::ProjectileMC(Actor* owner, int update_order)
    :MoveComponent(owner, update_order)
{
    
}

void ProjectileMC::Update(float deltatime){
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

		m_owner->SetPosition(pos);
        // std::cout << "x: " << m_owner->GetPosition().x << " y: " << m_owner->GetPosition().y << "\n";
    }
}
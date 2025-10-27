#include "follow_move_component.h"

FollowMC::FollowMC(Actor* owner, int update_order)
    :MoveComponent(owner, update_order)
    ,m_target_pos(owner->GetPosition())
    ,m_hor_border(0.f)
    ,m_ver_border(0.f)
{

}

void FollowMC::Update(float deltatime){
    if(GetAngularSpeed() != 0)
    {
        auto diff_vec = m_target_pos - m_owner->GetPosition();
        auto computed_rad = Vector2::GetRotationAngleRad(m_owner->GetForward(), diff_vec);
        auto delta_angle_rad = (computed_rad >= 0) ? std::min<float>(computed_rad, GetAngularSpeed())
                                                    :std::max<float>(computed_rad, -GetAngularSpeed());
        m_owner->Rotate(-delta_angle_rad);

    }
    auto pos = m_owner->GetPosition() + m_owner->GetForward() * GetForwardSpeed() * deltatime;
    if(m_hor_border != 0.f && pos.x < m_hor_border){
        pos.x = m_hor_border;
    }
    if(m_ver_border != 0.f && pos.y < m_hor_border){
        pos.y = m_hor_border;
    }
    m_owner->SetPosition(pos);
}
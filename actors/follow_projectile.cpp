#include "follow_projectile.h"
#include "game.h"

FollowProjectile::FollowProjectile(Game* game, const std::string& sprite_filename)
    :Actor(game)
    ,m_sc(nullptr)
    ,m_fmc(nullptr)
{
    m_sc = new SpriteComponent(this, 30);
    m_sc->SetTexture(game->GetTexture(sprite_filename));

    m_fmc = new FollowMC(this, 30);
    m_fmc->SetAngularSpeed(0.002f);
    m_fmc->SetForwardSpeed(800.f);
}

void FollowProjectile::SetProjectileAngularSpeed(float val){
    if(!m_fmc) return;
    m_fmc->SetAngularSpeed(val);
}

void FollowProjectile::SetProjectileForwardSpeed(float val){
    if(!m_fmc) return;
    m_fmc->SetForwardSpeed(val);
}

void FollowProjectile::UpdateActor(float deltatime){
    if((GetPosition().x < 0 || GetPosition().x > GetGame()->GetWindowWidth()) ||
       (GetPosition().y < 0 || GetPosition().y > GetGame()->GetWindowHeight())){
        SetState(State::Dead);
    }
    else{
        if(m_fmc){
            m_fmc->SetTargetPos(GetGame()->GetShipPosition());
        }
    }
}

void FollowProjectile::SetTargetPosition(const Vector2& vec){
    if(!m_fmc) return;
    m_fmc->SetTargetPos(vec);
}
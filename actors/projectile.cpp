#include "projectile.h"
#include "game.h"

Projectile::Projectile(Game* game,  const std::string& sprite_filename)
    :Actor(game)
    ,m_sc(nullptr)
    ,m_mc(nullptr)
    ,m_owner(nullptr)
    ,m_piercing(false)
{
    m_sc = new SpriteComponent(this, 30);
    m_sc->SetTexture(game->GetTexture(sprite_filename));

    m_circle = new CircleComponent(this, 30);
    m_circle->SetRadius(static_cast<float>(m_sc->GetTextureWidth() / 2));
}

void Projectile::SetProjectileAngularSpeed(float val){
    if(!m_mc) return;
    m_mc->SetAngularSpeed(val);
}

void Projectile::SetProjectileForwardSpeed(float val){
    if(!m_mc) return;
    m_mc->SetForwardSpeed(val);
}

void Projectile::UpdateActor(float deltatime){
    auto rot = Actor::GetRotation();
    if(GetState() == State::Dead) return;
    if((GetPosition().x < 0 || GetPosition().x > GetGame()->GetWindowWidth()) ||
       (GetPosition().y < 0 || GetPosition().y > GetGame()->GetWindowHeight())){
        SetState(State::Dead);
    }

}
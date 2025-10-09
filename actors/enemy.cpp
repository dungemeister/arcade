#include "enemy.h"
#include "sprite_component.h"
#include "enemy_projectile.h"
#include "follow_projectile.h"
#include "game.hpp"
#include "follow_move_component.h"

Enemy::Enemy(Game* game, const std::string& sprite_filename)
    :Actor(game)
    ,m_ship_position()
    ,m_fmc(nullptr)
    ,m_shoot_cooldown_period(2.f)
    ,m_shoot_cooldown_time(0.f)
{
    SpriteComponent *sc = new SpriteComponent(this, 100);
    sc->SetTexture(GetGame()->GetTexture(sprite_filename));

    m_fmc = new FollowMC(this, 30);
    m_fmc->SetAngularSpeed(0.02f);
    // m_fmc->SetForwardSpeed(200.f);
    // m_fmc->SetHorizontalBorder(1200.f);

    m_circle = new CircleComponent(this, 30);
    m_circle->SetRadius(sc->GetTextureHeight());
    SDL_Log("Enemy: [%p]", this);
}
Enemy::~Enemy(){
    GetGame()->RemoveEnemy(this);
}

void Enemy::UpdateActor(float deltatime){
    //TODO: objects interception and state checking/disabling
    m_shoot_cooldown_time -= deltatime;
    if(m_shoot_cooldown_time < 0.f) m_shoot_cooldown_time = 0.f;
    m_fmc->SetTargetPos(GetGame()->GetShipPosition());

    if(m_shoot_cooldown_time == 0.f)
    {
        
        EnemyProjectile* laser = new EnemyProjectile(GetGame(), "Assets/Laser.png");
        // FollowProjectile* laser = new FollowProjectile(GetGame(), "Assets/Laser.png");
        
        FollowMC* fmc = new FollowMC(laser, 30);
        fmc->SetTargetPos(GetGame()->GetShipPosition());
        laser->SetMoveStrategy(fmc);

        laser->SetRotation(GetRotation());
        laser->SetPosition(GetPosition());
        laser->SetProjectileForwardSpeed(500.f);
        laser->SetScale(2.f);

        m_shoot_cooldown_time = m_shoot_cooldown_period;
    }
}
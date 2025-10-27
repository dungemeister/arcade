#include "spawn_component.h"
#include "enemy.h"
#include "game.h"
#include "random.h"
#include "follow_move_component.h"

SpawnComponent::SpawnComponent(Actor* owner, int update_order)
    :Component(owner)
    ,m_enemies_spawn(10)
    ,m_spawn_time(5.f)
    ,m_spawn_cooldown(0.f)
{

}

void SpawnComponent::Update(float deltatime){
    m_spawn_cooldown -= deltatime;

    if(m_spawn_cooldown <= 0){
        SpawnEnemies();
        m_spawn_cooldown = m_spawn_time;
    } 
}

void SpawnComponent::SpawnEnemies(){
    if(!m_owner) return;

    auto width = m_owner->GetGame()->GetWindowWidth();
    auto height = m_owner->GetGame()->GetWindowHeight();

    auto enemies_spawned = Enemy::GetEnemiesAmount();
    for(int i = 0; i < m_enemies_spawn - enemies_spawned; i++){
        auto enemy = new Enemy(m_owner->GetGame(), "Assets/Enemy.png");
        enemy->SetPosition({static_cast<float>(width + 50), Random::GetFloatRange(50.f, height - 50.f)});
        enemy->SetScale(2.f);
        enemy->SetRotation(MyMath::Pi);

        auto fmc = new FollowMC(enemy, 30);
        fmc->SetAngularSpeed(0.02f);
        fmc->SetForwardSpeed(200.f);
        fmc->SetHorizontalBorder(1200.f);
        fmc->SetVerticalBorder(0.f);
        fmc->SetTargetPos({1700.f, Random::GetFloatRange(100, 800)});
    }
}
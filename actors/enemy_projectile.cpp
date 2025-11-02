#include "enemy_projectile.h"
#include "game.h"

EnemyProjectile::EnemyProjectile(Game* game, const std::string& sprite_filename)
    :Projectile(game, sprite_filename)
{
    SDL_Log("Enemy proj: [%p]", this);
}

void EnemyProjectile::UpdateActor(float deltatime){
    if(GetState() == State::Dead) return;
    auto pos = GetPosition();
    if((pos.x < 0 || pos.x > GetGame()->GetWindowWidth()) ||
       (pos.y < 0 || pos.y > GetGame()->GetWindowHeight())){
        SetState(State::Dead);
    }
    for(auto ship:  GetGame()->GetShips())
    {
        if(CirclesIntersect(*ship->GetCircleComponent(), *GetCircleComponent()) && !ship->IsImmortal())
        {
            SetState(State::Dead);
            // ship->SetState(State::Dead);
            ship->HandleDamage(1);
            SDL_Log("Killed ship %p, with enemy proj %p", ship, this);
            break;
        }

    }
}
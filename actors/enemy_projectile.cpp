#include "enemy_projectile.h"
#include "game.h"

EnemyProjectile::EnemyProjectile(Game* game, const std::string& sprite_filename)
    :Projectile(game, sprite_filename)
{
    
}

void EnemyProjectile::UpdateActor(float deltatime){
    if(GetState() == State::Dead) return;
    if((GetPosition().x < 0 || GetPosition().x > GetGame()->GetWindowWidth()) ||
       (GetPosition().y < 0 || GetPosition().y > GetGame()->GetWindowHeight())){
        SetState(State::Dead);
    }
    for(auto ship:  GetGame()->GetShips())
    {
        if(CirclesIntersect(*ship->GetCircleComponent(), *GetCircleComponent()) && !ship->IsImmortal())
        {
            SetState(State::Dead);
            // ship->SetState(State::Dead);
            ship->HandleDamage();
            SDL_Log("Killed ship %p, with enemy proj %p", ship, this);
            break;
        }

    }
}
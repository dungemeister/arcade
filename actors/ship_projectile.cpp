#include "ship_projectile.h"
#include "game.h"

ShipProjectile::ShipProjectile(Game* game, const std::string& sprite_filename)
    :Projectile(game, sprite_filename)
{
    
}

void ShipProjectile::UpdateActor(float deltatime){
    if(GetState() == State::Dead) return;
    if((GetPosition().x < 0 || GetPosition().x > GetGame()->GetWindowWidth()) ||
       (GetPosition().y < 0 || GetPosition().y > GetGame()->GetWindowHeight())){
        SetState(State::Dead);
    }
    for(auto enemy: GetGame()->GetEnemies()){
        if(CirclesIntersect(*enemy->GetCircleComponent(), *GetCircleComponent()))
        {
            if(!IsPiercing())
                SetState(State::Dead);
            enemy->SetState(State::Dead);
            SDL_Log("Killed enemy %p, with ship proj %p", enemy, this);
            break;
        }
    }
}
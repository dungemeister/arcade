#include "asteroid.h"
#include "types.h"
#include "sprite_component.h"
#include "game.hpp"
#include "asteroid_move_component.h"
#include "random.h"

Asteroid::Asteroid(Game* game):
    Actor(game)
{
    SetScale(1.0f);
    Vector2 rand_pos = Random::GetVector({0.f, 100.f}, {game->GetWindowWidth(), game->GetWindowHeight()});
    SetPosition(rand_pos);
    // SetRotation(Random::GetFloatRange(MyMath::PiOver2, 3 * MyMath::PiOver2));
    // SetRotation(1.34f * MyMath::PiOver2);

    SpriteComponent* sc = new SpriteComponent(this, 100);
    sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

    AsteroidMC* amc = new AsteroidMC(this, 30);
    amc->SetForwardSpeed(Random::GetFloatRange(50.f, 200.f));
    amc->SetAngularSpeed(0.01f);

    SDL_Log("Asteroid: [%p]", this);
}
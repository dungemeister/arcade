#pragma once

#include "actor.hpp"
#include "circle_component.h"
#include "animated_sprite_component.h"
#include "input_component.h"

class Ship: public Actor{
public:
    Ship(class Game* owner);
    ~Ship();
    void UpdateActor(float deltatime) override;
    void ActorInput(const bool* state) override;
    void HandleDamage();
    void SetImmortality(bool state) { m_immortal = state; }
    bool IsImmortal() const { return m_immortal; }

    CircleComponent* GetCircleComponent() { return m_circle; }
private:
    
    float m_laser_cooldown_period;
    float m_laser_cooldown_time;
    int m_laser_shoot_key;

    float m_alt_laser_cooldown_period;
    float m_alt_laser_cooldown_time;
    int m_alt_laser_shoot_key;

    InputComponent* m_ic;
    AnimSpriteComponent* m_asc;
    CircleComponent* m_circle;

    bool m_immortal;

    void StartFlickAnimation();
};

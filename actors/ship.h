#pragma once

#include "actor.hpp"
#include "circle_component.h"
#include "animated_sprite_component.h"
#include "input_component.h"
#include "heath_component.h"
#include "energy_component.h"

class Ship: public Actor{
public:
    Ship(class Game* owner);
    ~Ship();
    void UpdateActor(float deltatime) override;
    void ActorInput(const bool* state) override;
    void HandleDamage(int damage);
    void AccumulateEnergy(float deltatime);
    void SetImmortality(bool state) { m_immortal = state; }
    bool IsImmortal() const { return m_immortal; }

    int GetHealth() const { return m_hc->GetHealth(); }
    int GetEnergy() const { return m_ec->GetEnergy(); }

    CircleComponent* GetCircleComponent() { return m_circle; }
private:
    
    float m_laser_cooldown_period;
    float m_laser_cooldown_time;
    int m_laser_shoot_key;

    float m_alt_laser_cooldown_period;
    float m_alt_laser_cooldown_time;
    int m_alt_laser_shoot_key;

    float m_energy_period;
    float m_energy_cooldown;
    InputComponent* m_ic;
    AnimSpriteComponent* m_asc;
    CircleComponent* m_circle;
    HealthComponent* m_hc;
    EnergyComponent* m_ec;

    bool m_immortal;

    void StartFlickAnimation();
};

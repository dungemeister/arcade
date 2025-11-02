#pragma once
#include "component.h"

class HealthComponent: public Component{
public:
    HealthComponent(Actor* owner, int update_order)
    :Component(owner, update_order)
    ,m_health(0)
    {

    }
    ~HealthComponent() = default;

    void SetHealth(int health) { m_health = health; }
    int GetHealth() const { return m_health; }

    void TakeDamage(int damage) { m_health -= damage; }
    void TakeHeal(int heal) { m_health += heal; }
private:
    int m_health;
};
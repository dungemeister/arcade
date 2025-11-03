#pragma once
#include "component.h"

class EnergyComponent: public Component{
public:
    EnergyComponent(Actor* owner, int update_order)
    :Component(owner, update_order)
    ,m_energy(0)
    ,m_max_energy(10)
    {

    }
    ~EnergyComponent() = default;
    
    void  SetEnergy(float energy)       { m_energy = energy; }
    float GetEnergy() const             { return m_energy; }

    void SetMaxEnergy(int energy)       { m_max_energy = energy; }
    int  GetMaxEnergy() const           { return m_max_energy; }
    void IncreaseMaxEnergy(int energy) { m_max_energy += energy; }
    
    bool SpendEnergy(float energy) {
        if(m_energy - energy < 0){
            return false;
        }

        m_energy -= energy;
        return true;
    }
    void AccumulateEnergy(float energy) {
        if(m_energy + energy > m_max_energy) return;
        
        m_energy += energy;
    }

private:
    float m_energy;
    int m_max_energy;
};
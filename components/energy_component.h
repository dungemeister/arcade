#pragma once
#include "component.h"

class EnergyComponent: public Component{
public:
    EnergyComponent(Actor* owner, int update_order)
    :Component(owner, update_order)
    ,m_energy(0)
    {

    }
    ~EnergyComponent() = default;
    
    void SetEnergy(int energy) { m_energy = energy; }
    int GetEnergy() const { return m_energy; }

    void SpendEnergy(int energy) { m_energy -= energy; }
    void AccumulateEnergy(int energy) { m_energy += energy;}

private:
    int m_energy;
};
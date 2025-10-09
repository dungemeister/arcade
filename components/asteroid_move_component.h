#pragma once
#include "move_component.h"

class AsteroidMC: public MoveComponent{
public:
    AsteroidMC(Actor* owner, int update_order);
    void Update(float deltatime) override;
};
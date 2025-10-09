#pragma once
#include "move_component.h"
#include "actor.hpp"

class ProjectileMC: public MoveComponent{
public:
    ProjectileMC(Actor* owner, int update_order);
    void Update(float deltatime) override;
    
};
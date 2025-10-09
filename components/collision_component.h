#pragma once

#include "component.h"

class CollisionComponnet: public Component{
public:
    CollisionComponnet(Actor* owner, int update_order);
};
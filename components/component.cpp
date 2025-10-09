#include "component.h"
#include "actor.hpp"

Component::Component(Actor* owner, int updateOrder):
    m_owner(owner),
    m_update_order(updateOrder)
{
    m_owner->AddComponent(this);
}

Component::~Component(){
    m_owner->RemoveComponent(this);
}

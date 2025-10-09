#ifndef HYBRID_COMPONENT_H
#define HYBRID_COMPONENT_H

#include "inttypes.h"

class Component{
public:
    Component(class Actor* owner, int updateOrder = 100);

    virtual ~Component();

    virtual void Update(float deltatime) {}

    int GetUpdateOrder() { return m_update_order; }
    virtual void ProcessInput(const bool* state) {}
    Actor* GetOwner() const { return m_owner; }
protected:

    Actor* m_owner;
    int m_update_order;
};
#endif //HYBRID_COMPONENT_H
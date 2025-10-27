#ifndef MOVE_COMPONENT_H
#define MOVE_COMPONENT_H

#include "component.h"
#include "actor.hpp"

class MoveComponent: public Component{
public:
    MoveComponent(class Actor* owner, int updateOrder);
    virtual ~MoveComponent() {};

    float GetAngularSpeed() const { return m_angular_speed; }
    float GetForwardSpeed() const { return m_forward_speed; }
    float GetVerticalSpeed() const { return m_vertical_speed; }

    void SetAngularSpeed(float val){ m_angular_speed = val; }
    void SetForwardSpeed(float val){ m_forward_speed = val; }
    void SetVerticalSpeed(float val) { m_vertical_speed = val; }

    virtual void Update(float deltatime) override;
private:
    float m_angular_speed;
    float m_forward_speed;
    float m_vertical_speed;
};
#endif //MOVE_COMPONENT_H
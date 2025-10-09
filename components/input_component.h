#pragma once
#include "newtonian_move_component.h"

class InputComponent: public MoveComponent{
public:
    InputComponent(Actor* owner, int update_order);
    void ProcessInput(const bool* state) override;
    void Update(float deltatime) override;
    //TODO: getters/setters
    void SetMaxForwardSpeed     (float forward_speed)       { m_max_forward_speed = forward_speed; }
    void SetMaxAngularSpeed     (float angular_speed)       { m_max_angular_speed = angular_speed; }
    void SetForwardKey          (int forward_key)           { m_forward_key = forward_key; }
    void SetBackKey             (int back_key)              { m_back_key = back_key; }
    void SetClockWiseKey        (int clockwise_key)         { m_clockwise_key = clockwise_key; }
    void SetCounterClockWiseKey (int counter_clockwise_key) { m_counter_clockwise_key = counter_clockwise_key; }

private:
    float m_max_forward_speed;
    float m_max_angular_speed;
    int m_forward_key;
    int m_back_key;

    int m_clockwise_key;
    int m_counter_clockwise_key;
};
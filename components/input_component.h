#pragma once
#include "newtonian_move_component.h"

class InputComponent: public MoveComponent{
public:
    InputComponent(Actor* owner, int update_order);
    void ProcessInput(const bool* state) override;
    void Update(float deltatime) override;
    //TODO: getters/setters
    void SetMaxForwardSpeed     (float forward_speed)       { m_max_forward_speed = forward_speed; }
    void SetMaxVerticalSpeed    (float vertical_speed)      { m_max_vertical_speed = vertical_speed; }
    void SetForwardKey          (int forward_key)           { m_forward_key = forward_key; }
    void SetBackKey             (int back_key)              { m_back_key = back_key; }
    void SetUpKey               (int up_key)                { m_up_key = up_key; }
    void SetDownKey             (int down_key)              { m_down_key = down_key; }

private:
    float m_max_forward_speed;
    float m_max_vertical_speed;
    int m_forward_key;
    int m_back_key;

    int m_up_key;
    int m_down_key;
};
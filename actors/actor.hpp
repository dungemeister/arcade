#ifndef HYBRID_ACTOR_H
#define HYBRID_ACTOR_H

#include "types.h"
#include "component.h"
#include "math.h"
#include <vector>

class Actor{
public:
    enum State{
        Active = 0,
        Paused,
        Dead
    };

    Actor(class Game* game);

    virtual ~Actor();
    
    void Update(float deltatime);
    void UpdateComponents(float deltatime);
    virtual void UpdateActor(float deltatime);

    State GetState()             const { return m_state; }
    const Vector2& GetPosition() const { return m_position; }
    float GetScale()             const { return m_scale; }
    float GetRotation()          const { return m_rotation; }

    void SetState(State state)      { m_state = state; }
    void SetPosition(const Vector2& pos)   { m_position = pos;}
    void SetRotation(float radians) { m_rotation = radians; }
    void SetScale(float scale)      { m_scale = scale; }

    void Rotate(float radians)      { m_rotation += radians; }
    void Move(const Vector2& vec)   { m_position += vec; }

    Vector2 GetForward() const { return Vector2(cosf(m_rotation), -sinf(m_rotation)); }
    Game* GetGame()                 {return m_game; }
    
    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);

    void ProcessInput(const bool* state);
    virtual void ActorInput(const bool* state) {};
private:
    State m_state;
    Game* m_game;

    Vector2 m_position;
    float m_scale;
    float m_rotation;

    std::vector<class Component*> m_components;
};
#endif //HYBRID_ACTOR_H
#pragma once
#include "actor.hpp"
#include "circle_component.h"
#include "sprite_component.h"
#include "move_component.h"
#include <string>

class Projectile: public Actor{
public:
    Projectile(Game* game, const std::string& sprite_filename);
    virtual void UpdateActor(float deltatime) override;
    void SetProjectileAngularSpeed(float val);
    void SetProjectileForwardSpeed(float val);
    CircleComponent* GetCircleComponent() { return m_circle; }
    void SetMoveStrategy(MoveComponent* mc) { m_mc = mc; }
    void SetPiercing(bool state) { m_piercing = state; }
    bool IsPiercing() const { return m_piercing; }
private:
	bool m_piercing;
    CircleComponent* m_circle;
    SpriteComponent *m_sc;
    MoveComponent *m_mc;

    Actor* m_owner;
};

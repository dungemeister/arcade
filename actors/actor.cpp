#include "actor.hpp"
#include "game.h"

Actor::Actor(Game* game):
    m_state(State::Active),
    m_game(game),
    m_position(0.f, 0.f),
    m_scale(1.f),
    m_rotation(0.f)
{
    m_game->AddActor(this);

}

Actor::~Actor(){
    m_game->RemoveActor(this);

    while(!m_components.empty()){
        delete m_components.back();
    }
}

void Actor::Update(float deltatime){
    if(m_state == State::Active){
        UpdateComponents(deltatime);
        UpdateActor(deltatime);
    }
}

void Actor::UpdateComponents(float deltatime){
    for(auto comp: m_components){
        comp->Update(deltatime);
    }
}

void Actor::UpdateActor(float deltatime){

}

void Actor::AddComponent(Component* component){
    int comp_order = component->GetUpdateOrder();
    auto iter = m_components.begin();
    for(; iter != m_components.end(); ++iter){
        if(comp_order < (*iter)->GetUpdateOrder()){
            break;
        }
    }

    m_components.insert(iter, component);
}

void Actor::RemoveComponent(Component* component){
    auto iter = std::find(m_components.begin(), m_components.end(), component);
    if(iter != m_components.end()){
        m_components.erase(iter);
    }
}

void Actor::ProcessInput(const bool* state){
    if(m_state == State::Active){
        for(auto component: m_components){
            component->ProcessInput(state);
        }
        ActorInput(state);
    }
}
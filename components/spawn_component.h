#pragma once 
#include "component.h"

class SpawnComponent: public Component{
public:
    SpawnComponent(class Actor* owner, int update_order);

    void SetSpawnTime(float time) { m_spawn_time = time; }
    void SetEnemiesSpawn(int qty) { m_enemies_spawn = qty;}
    
    float   GetSpawnTime()     const    { return m_spawn_time; }
    float   GetSpawnCooldown() const    { return m_spawn_cooldown; }
    int     GetEnemiesSpawn()  const    { return m_enemies_spawn; }


    void Update(float deltatime) override;

    void SpawnEnemies();
private:
    int m_enemies_spawn;
    float m_spawn_time;
    float m_spawn_cooldown;
};
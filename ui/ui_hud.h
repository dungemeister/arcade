#pragma once 
#include "ui_layout.h"
#include <vector>
#include <string>
#include "ui_text.h"

class UIHud: public UILayout{
public:
    UIHud(class Game* game);
    void IncreaseScore(int score);
    void UpdateHealth();
    void UpdateEnergy();
    void Update(float deltatime) override;
    void Draw() override;
private:
    std::vector<std::string> m_buffs;
    int m_score;
    double m_time;
    UIText* m_score_text;
    UIText* m_time_text;
    UIText* m_health_text;
    UIText* m_energy_text;

};
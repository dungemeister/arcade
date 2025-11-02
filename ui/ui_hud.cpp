#include "ui_hud.h"
#include "game.h"
#include "types.h"
#include <sstream>
#include <string>
#include <iomanip>

UIHud::UIHud(Game* game)
    :UILayout(game)
    ,m_score(0)
    ,m_time(0)
{
    auto width = game->GetWindowWidth();
    auto height = game->GetWindowHeight();
    m_score_text = new UIText("Score: 0", this);
    m_score_text->SetFontSize(24);
    m_score_text->SetPosition({width / 2 - m_score_text->GetSize().w,
                               height - m_score_text->GetSize().h});

    m_time_text = new UIText("00:00", this);
    m_time_text->SetFontSize(24);
    m_time_text->SetPosition({width / 2 - m_time_text->GetSize().w,
                              0});
    
    std::string tmp = std::to_string(game->GetShipHealth());

    m_health_text = new UIText("Health: " + tmp, this);
    m_health_text->SetFontSize(24);
    m_health_text->SetPosition({0, height - m_health_text->GetSize().h});

    tmp = std::to_string(game->GetShipEnergy());
    m_energy_text = new UIText("Energy: " + tmp, this);
    m_energy_text->SetFontSize(24);
    m_energy_text->SetPosition({0, height - m_health_text->GetSize().h - m_energy_text->GetSize().h});
}

void UIHud::IncreaseScore(int score){
    
    m_score += score;
    std::string tmp = "Score:" + std::to_string(m_score);
    m_score_text->SetText(tmp);
}

void UIHud::UpdateHealth(){
    auto tmp = "Health:" + std::to_string(GetGame()->GetShipHealth());
    m_health_text->SetText(tmp);
}

void UIHud::UpdateEnergy(){
    auto tmp = "Energy:" + std::to_string(GetGame()->GetShipEnergy());
    m_energy_text->SetText(tmp);
}

void UIHud::Update(float deltatime){
    m_time += deltatime;

    std::stringstream data;
    data << std::setw(2) << std::setfill('0')
         << std::to_string(static_cast<int>(m_time/60)) << ":"
         << std::setw(2) << std::setfill('0')
         << std::to_string(static_cast<int>(m_time)%60);
    m_time_text->SetText(data.str());
    UpdateHealth();
    UpdateEnergy();
}

void UIHud::Draw(){
    m_score_text->Draw();
    m_time_text->Draw();
    m_health_text->Draw();
    m_energy_text->Draw();
}
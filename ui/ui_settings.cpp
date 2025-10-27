#include "ui_settings.h"
#include "game.h"
#include "ui_slider.h"

UISettings::UISettings(Game* game)
    :UIHorLayout(game)
{
    m_rect.x = game->GetWindowWidth() / 2;
    m_rect.y = game->GetWindowHeight() / 2;

    UIText* text = new UIText(this);
    text->SetText("Diffucilty: TODO");
    PushBackWidget(text);

    // UISlider<int>* slider = new UISlider<int>(this);
    UISlider<int> slider(this);
    // PushBackWidget(slider);
    
    SetWindowAlignment(WindowAlignment::EWindowLeft);
    SetAlignment(Alignment::ECenter);
}

void UISettings::Draw(){
    for(auto widget: m_widgets){
        widget->Draw();
    }
}

void UISettings::Update(float deltatime){
    for(auto widget: m_widgets){
        widget->Update(deltatime);
    }
}
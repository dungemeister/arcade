#include "ui_settings.h"
#include "game.h"

UISettings::UISettings(Game* game)
    :UIHorLayout(game)
{
    m_rect.x = game->GetWindowWidth() / 2;
    m_rect.y = game->GetWindowHeight() / 2;

    UIText* text = new UIText(this);
    text->SetText("Diffucilty: TODO");
    PushBackWidget(text);
    
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
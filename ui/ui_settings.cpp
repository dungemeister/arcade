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

    std::vector<int> dots = {1,2,3,4,5,5,66,99,11};
    UISlider<int>* slider = new UISlider<int>(dots, this);
    PushBackWidget(slider);

    std::vector<std::string> data = {"test", "debug", "release"};
    UISlider<std::string>* s_slider = new UISlider<std::string>(data, this);
    PushBackWidget(s_slider);

    SetWindowAlignment(WindowAlignment::EWindowCenter);
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
void UISettings::HandleEvent(const SDL_Event& event){
    for(auto widget: m_widgets){
        widget->HandleEvent(event);
    }
}
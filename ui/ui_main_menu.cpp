#include "ui_main_menu.h"
#include "game.h"
#include "ui_button.h"

UIMainMenu::UIMainMenu(Game* game)
    :UIHorLayout(game)
{
    m_rect.x = game->GetWindowWidth() / 2;
    m_rect.y = game->GetWindowHeight() / 2;

    
    UIButton* button = new UIButton(this, "New Game");
    button->AddClickStrategy([this](){ m_game->StartGame(); });
    button->SetOpacityPulsing(true);
    button->SetScalePulsing(true);
    PushBackWidget(button);
    
    button = new UIButton(this, "Load");
    button->AddClickStrategy([](){});
    button->SetOpacityPulsing(true);
    button->SetScalePulsing(true);
    PushBackWidget(button);

    button = new UIButton(this, "Settings");
    button->AddClickStrategy([this](){ m_game->StartSettingsUI(); });
    button->SetOpacityPulsing(true);
    button->SetScalePulsing(true);
    PushBackWidget(button);

    button = new UIButton(this, "Quit");
    button->AddClickStrategy([this](){ m_game->SetRunning(false); });
    button->SetOpacityPulsing(true);
    button->SetScalePulsing(true);
    PushBackWidget(button);

    SetAlignment(Alignment::ECenter);
    SetWindowAlignment(WindowAlignment::EWindowCenter);
}

UIMainMenu::~UIMainMenu(){
    SDL_Log("UIMM");
}

void UIMainMenu::Update(float deltatime){
    for(auto widget: m_widgets){
        widget->Update(deltatime);
    }
}

void UIMainMenu::Draw(){
    if(GetState() == UILayout::State::EClosed) return;
    for(auto widget: m_widgets){
        widget->Draw();
    }
    DrawBorder();
}

void UIMainMenu::HandleEvent(const SDL_Event& event){
    
    for(auto widget: m_widgets){
        widget->HandleEvent(event);
    }

}

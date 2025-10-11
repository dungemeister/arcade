#include "ui_main_menu.h"
#include "game.h"
#include "ui_button.h"

UIMainMenu::UIMainMenu(Game* game)
    :UIHorLayout(game)
    ,m_max_width(0.f)
{
    m_rect.x = game->GetWindowWidth() / 2;
    m_rect.y = game->GetWindowHeight() / 2;

    
    UIButton* button = new UIButton(this, "New Game");
    button->AddClickStrategy([this](){ m_game->StartGame(); });
    button->SetOpacityPulsing(true);
    button->SetScalePulsing(true);
    PushBackWidget(button);
    
    button = new UIButton(this, "Load");
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

    UpdateMaxWidgetsWidth();
    SetWindowAlignment(WindowAlignment::Center);
    SetAlignment(Alignment::Center);
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
}

void UIMainMenu::HandleEvent(const SDL_Event& event){
    
    for(auto widget: m_widgets){
        widget->HandleEvent(event);
    }

}

void UIMainMenu::UpdateMaxWidgetsWidth(){
    for(auto widget: m_widgets){
        auto size = widget->GetSize();
        m_max_width = std::max(size.w, m_max_width);
    }
}

void UIMainMenu::SetWindowAlignment(WindowAlignment align){
    switch(align){
        case WindowAlignment::Left:
            m_rect.x = 0;
        break;
        case WindowAlignment::Right:
            m_rect.x = m_game->GetWindowWidth() - m_max_width;
        break;
        case WindowAlignment::Center:
            m_rect.x = (m_game->GetWindowWidth() - m_max_width) / 2;
            
        break;
        default:
            SDL_Log("Unknown layout alignment");
        break;
    }
}
#include "ui_main_menu.h"
#include "game.hpp"
#include "ui_button.h"

UIMainMenu::UIMainMenu(Game* game)
    :UILayout(game)
    ,m_rect()
{
    m_rect.x = game->GetWindowWidth() / 2;
    m_rect.y = game->GetWindowHeight() / 2;

    
    UIButton* button = new UIButton(this, "New Game");
    button->AddClickStrategy([this](){ m_game->StartGame(); });
    button->SetOpacityPulsing(true);
    button->SetScalePulsing(true);
    AddButtonVertical(button);
    
    button = new UIButton(this, "Load");
    button->SetOpacityPulsing(true);
    button->SetScalePulsing(true);
    AddButtonVertical(button);

    button = new UIButton(this, "Quit");
    button->AddClickStrategy([this](){ m_game->SetRunning(false); });
    button->SetOpacityPulsing(true);
    button->SetScalePulsing(true);
    AddButtonVertical(button);

    for(auto& button: m_buttons){
        UIButton::UISize size = button->GetSize();
        size.y += button->GetFontSize();
        button->SetSize(size);
    }

}

UIMainMenu::~UIMainMenu(){
    SDL_Log("UIMM");
}

void UIMainMenu::Update(float deltatime){
    for(auto button: m_buttons){
        button->Update(deltatime);
    }
}

void UIMainMenu::Draw(){
    for(auto button: m_buttons){
        button->Draw();
    }
}

void UIMainMenu::HandleEvent(const SDL_Event& event){
    for(auto button: m_buttons){
        button->HandleEvent(event);
    }
}

void UIMainMenu::AddButtonVertical(UIButton* button){
    SDL_FPoint pos = {};
    pos.x = m_rect.x;
    pos.y = m_rect.y + m_rect.h;

    m_rect.w = std::max(m_rect.w, button->GetSizePadding().w);
    m_rect.h += button->GetSizePadding().h;
    button->SetPosition(pos);

    m_buttons.push_back(button);
    
}
#include "ui_settings.h"
#include "game.h"

UISettings::UISettings(Game* game)
    :UILayout(game)
{
    m_rect.x = game->GetWindowWidth() / 2;
    m_rect.y = game->GetWindowHeight() / 2;

    UIText* text = new UIText(this);
    text->SetText("Diffucilty: TODO");
    AddWidgetVertical(text);

}

void UISettings::AddWidgetVertical(UIWidget* widget){
    SDL_FPoint pos = {};
    pos.x = m_rect.x;
    pos.y = m_rect.y + m_rect.h;

    m_rect.w = std::max(m_rect.w, widget->GetSizePadding().w);
    m_rect.h += widget->GetSizePadding().h;
    widget->SetPosition(pos);

    auto text = dynamic_cast<UIText*>(widget);
    if(text){
        m_texts.push_back(text);
        return;
    }

    auto button = dynamic_cast<UIButton*>(widget);
    if(button){
        m_buttons.push_back(button);
        return;
    }
}

void UISettings::Draw(){
    for(auto text: m_texts){
        text->Draw();
    }

    for(auto button: m_buttons){
        button->Draw();
    }
}

void UISettings::Update(float deltatime){
    for(auto text: m_texts){
        text->Update(deltatime);
    }

    for(auto button: m_buttons){
        button->Update(deltatime);
    }
}
#pragma once
#include "ui_layout.h"
#include "ui_text.h"
#include "ui_button.h"

class UISettings: public UILayout{
public:
    UISettings(class Game* game);

    void Draw() override;
    void Update(float delatime) override;

private:
    std::vector<UIButton*> m_buttons;
    std::vector<UIText*> m_texts;
    SDL_FRect m_rect;

    void AddWidgetVertical(UIWidget* widget);
};

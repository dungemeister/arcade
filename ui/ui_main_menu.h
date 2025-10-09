#pragma once
#include <vector>
#include <string>

#include "ui_button.h"
#include "ui_layout.h"

class UIMainMenu: public UILayout{
public:
    UIMainMenu(class Game* game);
    ~UIMainMenu();
    
    void Update(float deltatime) override;
    void Draw() override;
    void HandleEvent(const SDL_Event& event) override;
    void AddButtonVertical(UIButton* button);
private:
    std::vector<class UIButton*> m_buttons;
    SDL_FRect m_rect;
};
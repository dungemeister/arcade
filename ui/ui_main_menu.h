#pragma once
#include <vector>
#include <string>

#include "ui_button.h"
#include "ui_hor_layout.h"

class UIMainMenu: public UIHorLayout{
public:

    UIMainMenu(class Game* game);
    ~UIMainMenu();
    
    void Update(float deltatime) override;
    void Draw() override;
    void HandleEvent(const SDL_Event& event) override;
    
    
private:

};
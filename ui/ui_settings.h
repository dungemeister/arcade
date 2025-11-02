#pragma once
#include "ui_hor_layout.h"
#include "ui_text.h"
#include "ui_button.h"

class UISettings: public UIHorLayout{
public:
    UISettings(class Game* game);
    ~UISettings() = default;
    void Draw() override;
    void Update(float delatime) override;
    void HandleEvent(const SDL_Event& event) override;

private:

};

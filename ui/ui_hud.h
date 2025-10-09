#pragma once 
#include "ui_layout.h"
#include <vector>
#include <string>

class UIHud: public UILayout{
public:
    UIHud(class Game* game);
    void Draw() override;
private:
    std::vector<std::string> m_buffs;
};
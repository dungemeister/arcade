#include "ui_hud.h"
#include "game.hpp"
#include "types.h"

UIHud::UIHud(Game* game)
    :UILayout(game)
{
    m_buffs.push_back("1");
    m_buffs.push_back("2");
}

void UIHud::Draw(){

    
}
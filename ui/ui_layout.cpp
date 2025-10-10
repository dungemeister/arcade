#include "ui_layout.h"
#include "game.h"

UILayout::UILayout(Game* game)
    :m_game(game)
    ,m_state(UILayout::State::EClosed)
{
    GetGame()->AddUI(this);
}

UILayout::~UILayout(){
    while(!m_widgets.empty()){
        delete m_widgets.back();
    }
    GetGame()->RemoveUI(this);
}

void UILayout::RemoveWidget(UIWidget* widget){
    auto it = std::find(m_widgets.begin(), m_widgets.end(), widget);
    m_widgets.erase(it);
}
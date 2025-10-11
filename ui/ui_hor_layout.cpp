#include "ui_hor_layout.h"
#include "ui_widget.h"
#include "game.h"

UIHorLayout::UIHorLayout(Game* game)
    :UILayout(game)
{

}

void UIHorLayout::PushBackWidget(class UIWidget* widget){
    UILayout::AddWidget(widget);

    SDL_FPoint pos = {};
    pos.x = m_rect.x;
    pos.y = m_rect.y + m_rect.h;

    m_rect.w = std::max(m_rect.w, widget->GetSizePadding().w);
    m_rect.h += widget->GetSizePadding().h;
    widget->SetPosition(pos);
    
}

void UIHorLayout::SetAlignment(Alignment align){
    switch(align){
        case Alignment::Left:
            for(auto& widget: m_widgets){
                auto pos = widget->GetPosition();
                pos.x = m_rect.x;
                widget->SetPosition(pos);
            }
        break;
        case Alignment::Right:
            for(auto& widget: m_widgets){
                auto size = widget->GetSize();
                auto pos = widget->GetPosition();
                pos.x = (m_rect.x + m_rect.h) - size.w;
                widget->SetPosition(pos);
            }
        break;
        case Alignment::Center:
            for(auto& widget: m_widgets){
                auto size = widget->GetSize();
                auto pos = widget->GetPosition();
                pos.x = (m_rect.w - size.w) / 2 + m_rect.x;
                widget->SetPosition(pos);
            }
        break;
        default:
            SDL_Log("Unknown alignment");
        break;
    }
}
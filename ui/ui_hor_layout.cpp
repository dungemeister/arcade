#include "ui_hor_layout.h"
#include "ui_widget.h"
#include "game.h"
#include "palette.h"

UIHorLayout::UIHorLayout(Game* game)
    :UILayout(game)
    ,m_max_width(0.f)
{

}

void UIHorLayout::PushBackWidget(UIWidget* widget){
    UILayout::AddWidget(widget);

    SDL_FPoint pos = {};
    pos.x = m_rect.x;
    pos.y = m_rect.y + m_rect.h;
    widget->SetPosition(pos);

    m_rect.w = std::max(m_rect.w, widget->GetSizePadding().w);
    m_rect.h += widget->GetSizePadding().h;
}

void UIHorLayout::SetAlignment(Alignment align){
    switch(align){
        case Alignment::ELeft:
            for(auto& widget: m_widgets){
                auto pos = widget->GetPosition();
                pos.x = m_rect.x;
                widget->SetPosition(pos);
            }
        break;
        case Alignment::ERight:
            for(auto& widget: m_widgets){
                auto size = widget->GetSizePadding();
                auto pos = widget->GetPosition();
                pos.x = (m_rect.x + m_rect.h) - size.w;
                widget->SetPosition(pos);
            }
        break;
        case Alignment::ECenter:
            for(auto& widget: m_widgets){
                auto size = widget->GetSizePadding();
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

void UIHorLayout::SetWindowAlignment(WindowAlignment align){
    switch(align){
        case WindowAlignment::EWindowLeft:
            m_rect.x = 0;
        break;
        case WindowAlignment::EWindowRight:
            m_rect.x = m_game->GetWindowWidth() - m_rect.w;
        break;
        case WindowAlignment::EWindowCenter:
            m_rect.x = (m_game->GetWindowWidth() - m_rect.w) / 2;
            
        break;
        default:
            SDL_Log("Unknown layout alignment");
        break;
    }
    UpdateWidgetsHorizontalPosition();
}

void UIHorLayout::DrawBorder(){
    if(!m_game) return;

    auto renderer = m_game->GetRenderer();
    SDL_Color color = Colors::OceanSunset::midnight_green;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderRect(renderer, &m_rect);
}

void UIHorLayout::UpdateWidgetsHorizontalPosition(){
    for(auto& widget: m_widgets){
        auto pos = widget->GetPosition();
        pos.x = m_rect.x;
        widget->SetPosition(pos);
    }
}
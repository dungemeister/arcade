#include "ui_slider.h"
#include "ui_layout.h"
#include <SDL3/SDL.h>
#include <string>
#include <vector>
#include "palette.h"
#include "figure/circle.h"

template<typename T>
UISlider<T>::UISlider(const std::string& label, UILayout* layout)
    :UIWidget(layout)
{
    
}

template<typename T>
UISlider<T>::UISlider(UILayout* layout)
    :UIWidget(layout)
    ,m_cursor_active(false)
    ,m_cur_index(-1)
{
    m_color = Colors::Sunset::pantone;
    m_cursor_color = Colors::OceanSunset::bittersweet;
    m_border_color  = Colors::Sunset::saffron;
    m_text_color = Colors::OceanSunset::moonstone;

    m_rect.h = 20;
    m_rect.w = 400;
    if(!layout){
        
        SDL_Log("UISlider has no layout");
        return;
    }
    
}

template<typename T>
UISlider<T>::UISlider(const std::vector<T>& dots, UILayout* layout)
    :UISlider(layout)
{
    m_cursor.w = m_rect.w / dots.size();
    m_cursor.h = m_rect.h;

    m_dots = dots;
    for(auto dot: m_dots){
        UIText* text = nullptr;
        if constexpr (std::is_same_v<T, std::string>){
            text = new UIText(dot, layout);
        }
        else {
            text = new UIText(std::to_string(dot), layout);
        }
        text->SetHiden(true);
        text->SetColor(Colors::OceanSunset::moonstone);
        m_texts.push_back(text);
    }
    if(m_dots.size() > 0)
        SetIndex(0);
}

template<typename T>
void UISlider<T>::Draw(){
    if(!m_layout) return;

    UpdateTextPosition();

    auto renderer = m_layout->GetGame()->GetRenderer();
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // float circle_radius = m_rect.h * 1.5;
    // SDL_Color dot_color = Colors::OceanSunset::midnight_green;
    // for(int i = 0; i < m_dots.size(); i++){
    //     int center_x = m_rect.x + (m_rect.w / (m_dots.size() - 1)) * i;
    //     int center_y = m_rect.y + m_rect.h / 2;
    //     // CircleOutline::DrawCircle(renderer, center_x, center_y, circle_radius, dot_color);
    //     auto text = m_texts[i];
    //     auto text_size = text->GetSize();
    //     float offset_x = -(text_size.w / 2);
    //     // float offset_y = (circle_radius + text_size.h);
    //     float offset_y = -(circle_radius);
    // }
    
    int border_padding = 2;
    SDL_FRect border = m_rect;
    border.x -= border_padding;
    border.y -= border_padding;
    border.w += border_padding << 1;
    border.h += border_padding << 1;
    
    SDL_SetRenderDrawColor(renderer, m_border_color.r, m_border_color.g, m_border_color.b, 255); // Белый цвет
    SDL_RenderFillRect(renderer, &border);
    
    SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, 128); // Белый цвет
    SDL_RenderFillRect(renderer, &m_rect);

    SDL_SetRenderDrawColor(renderer, m_cursor_color.r, m_cursor_color.g, m_cursor_color.b, 255); // Белый цвет
    SDL_RenderFillRect(renderer, &m_cursor);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Белый цвет
    SDL_RenderRect(renderer, &m_rect_padding);

}

template<typename T>
void UISlider<T>::Update(float deltatime){

}

template<typename T>
void UISlider<T>::HandleEvent(const SDL_Event& event){
    SDL_FPoint pos = {};
    switch(event.type){
        case SDL_EVENT_MOUSE_MOTION:
            pos = {event.motion.x, event.motion.y};
            Hovered(pos);
            if(GetCursorState()) OnClick(pos);
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if(IsHovered()) OnClick({event.motion.x, event.motion.y});
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            SetCursorState(false);
            break;
        
    }
}

template<typename T>
void UISlider<T>::SetPosition(const SDL_FPoint& pos){
    m_rect.x = pos.x;
    m_rect.y = pos.y;
    UpdatePadding();
    UpdateCursorPosition(pos);
    UpdateTextPosition();
}

template<typename T>
void UISlider<T>::SetIndex(int index){
    if(index < m_dots.size() && index >= 0){
        m_cur_index = index;
    }
    UpdateValue();
}

template<typename T>
void UISlider<T>::UpdateCursorPosition(const SDL_FPoint& pos){
    
    if(m_cur_index > 0){
        m_cursor.x = pos.x + m_cursor.w * m_cur_index;
        m_cursor.y = pos.y;
    }
    else{
        m_cursor.x = pos.x + m_cursor.w * 0;
        m_cursor.y = pos.y;
    }
}

template<typename T>
void UISlider<T>::OnClick(const SDL_FPoint& point){
    UpdateCursorX(point.x);
    SetCursorState(true);
    if(m_on_click)
        m_on_click(point);
}

template<typename T>
void UISlider<T>::SetRange(T start, T stop, T step){
    for(auto i = start; i <= stop; i += step){
        m_dots.push_back(i);
    }
}

template<typename T>
void UISlider<T>::UpdateTextPosition(){
    for(auto text: m_texts){
        auto size = text->GetSize();
        text->SetPosition({m_rect.x + (m_rect.w - size.w) / 2, m_rect.y});
    }
}

template<typename T>
void UISlider<T>::UpdateValue(){
    for(int i = 0; i < m_texts.size(); i++){
        if(i == m_cur_index)
            m_texts[i]->SetHiden(false);
        else
            m_texts[i]->SetHiden(true);
    }
}
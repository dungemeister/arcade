#include "ui_button.h"
#include "ui_layout.h"
#include "SDL3/SDL.h"
#include <SDL3_ttf/SDL_ttf.h>
#include "game.h"
#include "palette.h"

UIButton::UIButton(class UILayout* layout, const std::string& text)
    :UIWidget(layout)
    ,m_text(text)
    ,m_texture(nullptr)
    ,m_font(nullptr)
    ,m_font_size(24)
    ,m_scale_pulsing(false)
    ,m_pulse_val(0.f)
    ,m_pulse_speed(5.f)
    ,m_scale_min(0.85)
    ,m_scale_max(1.15)
    ,m_opacity_pulsing(false)
    ,m_opacity_min(0.f)
    ,m_opacity_max(1.f)
    ,m_opacity(0.f)
{
    m_color = Colors::OceanSunset::moonstone;
    
    m_renderer = m_layout->GetGame()->GetRenderer();
    m_font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", m_font_size);
    if(!m_font) SDL_Log("%s", SDL_GetError());

    auto size = GetSize();

    m_surface = TTF_RenderText_Blended_Wrapped(m_font, m_text.c_str(), 0, m_color, 0);
    if(!m_surface){
        SDL_Log("%s", SDL_GetError());
        return;
    }
    size.w = m_surface->w;
    size.h = m_surface->h;
    SetSize(size);
    
    int x_padding = 5;
    int y_padding = 5;
    m_rect_padding = size;
    m_rect_padding.x -= x_padding;
    m_rect_padding.y += y_padding;
    m_rect_padding.w += x_padding * 2;
    m_rect_padding.h += y_padding * 2;

    m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
    if(!m_texture){
        SDL_Log("%s", SDL_GetError());
        return;
    }
}

UIButton::UIButton()
    :UIButton(nullptr, "")
{

}

void UIButton::SetFontSize(int size) {
    m_font_size = size;
    m_font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", m_font_size);
    if(!m_font) SDL_Log("%s", SDL_GetError());
}

void UIButton::Update(float deltatime){
    m_pulse_val += m_pulse_speed * deltatime;
    if(IsHovered()){
        if(m_scale_pulsing){
        
            m_scale = m_scale_min + (SDL_sinf(m_pulse_val) + 1.0f) * 0.5f * (m_scale_max - m_scale_min);
            
            float newWidth = GetSize().w * m_scale;
            float newHeight = GetSize().h * m_scale;
            float newX = GetSize().x + (GetSize().w - newWidth) * 0.5f;
            float newY = GetSize().y + (GetSize().h - newHeight) * 0.5f;
            
            m_dst_rect.x = newX;
            m_dst_rect.y = newY;
            m_dst_rect.w = newWidth;
            m_dst_rect.h = newHeight;

        }
        
        if(m_opacity_pulsing){
            m_opacity = m_opacity_min + (SDL_sinf(m_pulse_val) + 1.0f) * 0.5f * (m_opacity_max - m_opacity_min);
        }
        if(m_on_hovered) m_on_hovered();
    }
    else{
        m_dst_rect = GetSize();
    }

}

void UIButton::Draw(){
    DrawBackground();
    DrawBorder();
    DrawText();

}

void UIButton::HandleEvent(const SDL_Event& event){
    switch(event.type){
        case SDL_EVENT_MOUSE_MOTION:
            Hovered({event.motion.x, event.motion.y});
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            if(m_on_click && IsHovered()) OnClick();
            break;
    }
}

void UIButton::OnClick(){
    auto size = GetSize();
    auto renderer = m_layout->GetGame()->GetRenderer();

    m_on_click();

}



void UIButton::DrawBackground(){
    if(IsHovered()){
        if(m_opacity_pulsing)
        {
            m_color.a = 128 * m_opacity;
            
            SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(m_renderer, m_color.r, m_color.g, m_color.b, m_color.a); // Белый цвет

            // SDL_RenderRect(renderer, &rect);
            SDL_RenderFillRect(m_renderer, &m_dst_rect);

        }
    }
}

void UIButton::DrawBorder(){
    if(!m_layout->GetGame()) return;

    auto renderer = m_layout->GetGame()->GetRenderer();
    SDL_Color color = Colors::OceanSunset::midnight_green;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderRect(renderer, &m_rect);
}

void UIButton::DrawText(){
    if(IsHovered()){
        m_color = Colors::OceanSunset::atomic_tangerine;
        
        SDL_RenderTexture(m_renderer, m_texture, NULL, &m_dst_rect);
    }
    else{
        auto size = GetSize();
        SDL_RenderTexture(m_renderer, m_texture, NULL, &size);

    }
}

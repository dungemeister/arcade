#include "ui_text.h"
#include "ui_layout.h"
#include "game.h"
#include "palette.h"

UIText::UIText(class UILayout* layout)
    :UIWidget(layout)
    ,m_texture(nullptr)
    ,m_font(nullptr)
    ,m_font_size(16)
    ,m_text()
{
    m_color = Colors::OceanSunset::bittersweet;
}

UIText::~UIText(){
    SDL_DestroyTexture(m_texture);
    TTF_CloseFont(m_font);
}

void UIText::UpdateTexture(){
    if(m_texture){
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }
    if(m_text.empty()) return;

    auto surface = CreateSurface(m_text);
    if(surface){
        m_texture = SDL_CreateTextureFromSurface(m_layout->GetGame()->GetRenderer(), surface);
        m_rect.w = surface->w;
        m_rect.h = surface->h;
        SDL_DestroySurface(surface);
    }
}

void UIText::SetText(const std::string& text){
    m_text = text;
    UpdateTexture();

}

void UIText::Update(float deltatime){

}

void UIText::Draw(){
    auto render = m_layout->GetGame()->GetRenderer();
    if(m_texture){
        SDL_RenderTexture(render, m_texture, NULL, &m_rect);
    }
}

SDL_Surface* UIText::CreateSurface(const std::string& text){
    m_font = TTF_OpenFont(m_font_path.c_str(), m_font_size);
    auto res = TTF_SetFontDirection(m_font, TTF_Direction::TTF_DIRECTION_LTR);
    if(!res){
        SDL_Log("%s", SDL_GetError());
    }
    return TTF_RenderText_Blended(m_font, text.c_str(), text.size(), m_color);
}


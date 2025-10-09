#include "sprite_component.h"
#include "math.h"
#include "actor.hpp"
#include "game.hpp"

SpriteComponent::SpriteComponent(Actor* owner, int draw_order):
    Component(owner)
    ,m_texture(nullptr)
    ,m_draw_order(draw_order)
    ,m_text_width(0)
    ,m_text_height(0)
    ,m_flick_time_period(0.f)
    ,m_flick_time(0.f)
    ,m_texture_alpha(255)
    ,m_flick_qty(0)
{
    m_owner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent(){
    m_owner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::SetTexture(SDL_Texture* texture){
    m_texture = texture;

    SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
    SetTextureAlpha(m_texture, m_texture_alpha);
    auto res = SDL_GetTextureSize(m_texture, &m_text_width, &m_text_height);
    if(!res){
        SDL_Log("Failed to get widht and height from texture");
    }
}

void SpriteComponent::Draw(SDL_Renderer* renderer){

    if(m_texture){
        SDL_FRect r;
        r.w = m_text_width * m_owner->GetScale();
        r.h = m_text_height * m_owner->GetScale();

        r.x = m_owner->GetPosition().x - r.w / 2;
        r.y = m_owner->GetPosition().y - r.h / 2;

        SDL_RenderTextureRotated(renderer, m_texture, nullptr, &r,  -MyMath::ToDegrees(m_owner->GetRotation()), nullptr, SDL_FLIP_NONE);

    }
    else{
        //TODO: debug this code
        SDL_Rect r;
        r.w = m_text_width * m_owner->GetScale();
        r.h = m_text_height * m_owner->GetScale();

        r.x = m_owner->GetPosition().x - r.w / 2;
        r.y = m_owner->GetPosition().y - r.h / 2;
        SDL_Surface* surface = SDL_GetWindowSurface(m_owner->GetGame()->GetWindow());
        SDL_FillSurfaceRect(surface, &r, 0xFFFFFFFF);
    }
}

void SpriteComponent::Update(float deltatime){
    if(m_flick_time_period > 0.f && m_flick_qty > 0){
        m_flick_time -= deltatime;
        if(m_flick_time <= 0.f)
        {
            m_flick_time = m_flick_time_period;
            m_flick_qty--;
            FlickTexture(m_texture, m_texture_alpha + 128);
            auto ship = dynamic_cast<Ship*>(m_owner);
            if(ship && m_flick_qty == 0){
                ship->SetImmortality(false);
            }
        }
    }
}

void SpriteComponent::FlickTexture(SDL_Texture* text, uint8_t alpha){
    if(text)   
        SetTextureAlpha(text, alpha);
}

void SpriteComponent::SetTextureAlpha(SDL_Texture* text, uint8_t alpha){
    m_texture_alpha = alpha;
    if(text){
        SDL_SetTextureAlphaMod(text, alpha);
    }
}
#include "animated_sprite_component.h"

AnimSpriteComponent::AnimSpriteComponent(class Actor* owner, int draw_order):
    SpriteComponent(owner, draw_order),
    m_curr_frame(0.f),
    m_anim_fps(24.f)
{
    
}

void AnimSpriteComponent::Update(float deltatime){
    SpriteComponent::Update(deltatime);

    if(m_anim_textures.size() > 0){
        m_curr_frame += deltatime * m_anim_fps;

        while(m_curr_frame >= m_anim_textures.size()){
            m_curr_frame -= m_anim_textures.size();
        }
        SetTexture(m_anim_textures[static_cast<int>(m_curr_frame)]);
    }

}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures){
    m_anim_textures = textures;

    if(m_anim_textures.size() > 0){
        m_curr_frame = 0.f;
        SetTexture(m_anim_textures[0]);
    }
}
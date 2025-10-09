#include "background_sprite_component.h"
#include "actor.hpp"

BackgroundSpriteComponent::BackgroundSpriteComponent(Actor* owner, int drawOrder):
    SpriteComponent(owner, drawOrder),
    m_scroll_speed(0.f),
    m_screen_size(0.f, 0.f)
{

}

void BackgroundSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures){
    int count = 0;
    for(auto tex: textures){
        BGTexture temp;

        temp.m_texture = tex;

        temp.m_offset.x = count * m_screen_size.x;
        temp.m_offset.y = 0;

        m_textures.emplace_back(temp);
        count++;
    }
}

void BackgroundSpriteComponent::Update(float deltatime){

    for(auto& bg: m_textures){
        bg.m_offset.x += m_scroll_speed * deltatime;

        if(bg.m_offset.x < -m_screen_size.x){
            bg.m_offset.x = (m_textures.size() - 1) * m_screen_size.x - 1;
        }
    }
}

void BackgroundSpriteComponent::Draw(SDL_Renderer* renderer){
    for(auto& bg: m_textures){
        SDL_FRect r;
		// Assume screen size dimensions
		r.w = static_cast<int>(m_screen_size.x);
		r.h = static_cast<int>(m_screen_size.y);
		// Center the rectangle around the position of the owner
		// r.x = static_cast<int>(m_owner->GetPosition().x - r.w / 2 + bg.m_offset.x);
		// r.y = static_cast<int>(m_owner->GetPosition().y - r.h / 2 + bg.m_offset.y);
        
        r.x = bg.m_offset.x;
        r.y = bg.m_offset.y;
		// Draw this background
		SDL_RenderTexture(renderer, bg.m_texture, nullptr, &r);

    }
}
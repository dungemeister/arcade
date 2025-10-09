#ifndef HYBRID_ANIMATED_SPRITE_COMPONENT_H
#define HYBRID_ANIMATED_SPRITE_COMPONENT_H

#include "sprite_component.h"
#include <vector>
#include <SDL3/SDL.h>

class AnimSpriteComponent: public SpriteComponent{
public: 
    AnimSpriteComponent(class Actor* owner, int draw_order=100);
    
    void Update(float deltatime);

    void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
    float GetAnimFPS() const { return m_anim_fps;}
    void SetAnimFPS(float fps) { m_anim_fps = fps;}

private:
    class Actor* m_owner;
    std::vector<SDL_Texture*> m_anim_textures;
    float m_anim_fps;
    float m_curr_frame;
};
#endif //HYBRID_ANIMATED_SPRITE_COMPONENT_H
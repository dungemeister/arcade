#ifndef HYBRID_BACKGROUND_SPRITE_COMPONENT_H
#define HYBRID_BACKGROUND_SPRITE_COMPONENT_H

#include "sprite_component.h"
#include <vector>
#include <SDL3/SDL.h>
#include "types.h"

class BackgroundSpriteComponent: public SpriteComponent
{
public:
    BackgroundSpriteComponent(class Actor* owner, int drawOrder=10);
    void Update(float deltatime) override;
    void Draw(SDL_Renderer* renderer) override;
    void SetBGTextures(const std::vector<SDL_Texture*>& textures);

    void SetScreenSize(const Vector2& size) { m_screen_size = size; }
    void SetScrollSpeed(float speed)         { m_scroll_speed = speed; }
    float GetScrollSpeed()                  { return m_scroll_speed; }
private:
    struct BGTexture{
        SDL_Texture* m_texture;
        Vector2 m_offset;
    };

    class Actor* m_owner;
    std::vector<BGTexture> m_textures;
    Vector2 m_screen_size;
    float m_scroll_speed;

};
#endif //HYBRID_BACKGROUND_SPRITE_COMPONENT_H
#ifndef HYBRID_SPRITE_COMPONENT_H
#define HYBRID_SPRITE_COMPONENT_H

#include "component.h"
#include "SDL3/SDL.h"

class SpriteComponent: public Component{
public:
    SpriteComponent(class Actor* owner, int drawOrder);
    ~SpriteComponent();

    virtual void Draw       (SDL_Renderer* renderer);
    virtual void SetTexture (SDL_Texture*  texture);
    void Update(float deltatime) override;
    
    void FlickTexture(SDL_Texture* text, uint8_t alpha);
    void SetTextureAlpha(SDL_Texture* text, uint8_t alpha);

    void SetFlickQty    (int qty)   { m_flick_qty = qty; }
    void SetFlickPeriod(float time) { m_flick_time_period = time; }
    int GetTextureWidth()           { return m_text_width; }
    int GetTextureHeight()          { return m_text_height; }
    int GetDrawOrder()              { return m_draw_order; }
protected:
    SDL_Texture* m_texture;
    int m_draw_order;
    float m_text_width, m_text_height;

    float m_flick_time_period, m_flick_time;
    int m_flick_qty;
    uint8_t m_texture_alpha;
};
#endif //HYBRID_SPRITE_COMPONENT_H
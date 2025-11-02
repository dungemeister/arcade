#pragma once
#include "ui_widget.h"
#include <string>
#include <functional>

class UIButton: public UIWidget{
public:
    enum State{
        ButtonNormal,
        ButtonHovered,
        ButtonPressed,
    };

    UIButton(class UILayout* layout, const std::string& );
    UIButton();
    virtual ~UIButton() = default;
    
    UIButton(const UIButton& other)
        :UIWidget(other)
        ,m_text(other.GetText())
    {
    }
    void SetText(const std::string& text) { m_text = text; }
    std::string GetText() const { return m_text; }

    int GetFontSize() const { return m_font_size; }
    void SetFontSize(int size);

    void SetOpacityPulsing(bool state)  { m_opacity_pulsing = state; }
    bool GetOpacityPulsing() const      { return m_opacity_pulsing; }

    void SetScalePulsing(bool state)    { m_scale_pulsing = state; }
    bool GetScalePulsing() const        { return m_scale_pulsing; }
    
    void Update(float deltatime) override;
    void Draw() override;
    void HandleEvent(const SDL_Event& event) override;

    void OnClick();
    void AddClickStrategy(std::function<void()> cb) { m_on_click = cb; }
private:
    std::string m_text;
    struct SDL_Texture* m_texture;
    struct SDL_Renderer* m_renderer;
    struct SDL_Surface* m_surface;
    struct TTF_Font* m_font;
    int m_font_size;
    struct SDL_Color m_color;
    
    SDL_FRect m_dst_rect;
    
    float m_pulse_val;
    float m_pulse_speed;
//Для анимации пульсации масштабирования
    bool m_scale_pulsing;
    float m_scale;
    float m_scale_min;
    float m_scale_max;
//Для анимации пульсации прозрачности
    bool m_opacity_pulsing;
    float m_opacity_min;
    float m_opacity_max;
    float m_opacity;

    std::function<void()> m_on_click;
    std::function<void()> m_on_hovered;
    std::function<void()> m_on_pressed;

    void DrawBackground();
    void DrawBorder();
    void DrawText();
};
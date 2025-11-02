#pragma once
#include "ui_widget.h"
#include <vector>
#include "ui_text.h"
#include <functional>

template<typename T>
class UISlider: public UIWidget{
public:
    // UISlider()
    UISlider(const std::string& label, class UILayout* layout);
    UISlider(class UILayout* layout);
    UISlider(const std::vector<T>& dots, class UILayout* layout);
    ~UISlider() = default;
    
    void SetPosition(const SDL_FPoint& pos) override;
    void Update(float deltatime) override;
    void Draw() override;
    void HandleEvent(const SDL_Event& event) override;
    void SetRange(T start, T stop, T step);
    void UpdateCursorX(float x) {
        int index = (x - m_rect.x) / m_cursor.w;
        if(index == m_cur_index) return;
        if(index >= 0 && index < m_dots.size()){
            m_cursor.x = m_rect.x + m_cursor.w * index;
            SetIndex(index);
        } 

    }
    void SetIndex(int index);
    T GetCurrentValue() const { return m_dots[m_cur_index]; }
    void OnClick(const SDL_FPoint& point);
    void SetCursorState(bool state) { m_cursor_active = state; }
    void UpdateCursorPosition(const SDL_FPoint& pos);
    bool GetCursorState() const { return m_cursor_active; }

    void UpdateTextPosition();

private:
    std::vector<T> m_dots;
    std::vector<UIText*> m_texts;
    SDL_Color m_color;
    SDL_Color m_cursor_color;
    SDL_Color m_border_color;
    SDL_Color m_text_color;
    SDL_FRect m_cursor;
    bool m_cursor_active;
    int m_cur_index;

    std::function<void(const SDL_FPoint&)> m_on_click;

    void UpdateValue();
};

//Template file .tpp
#include "ui_slider.cpp"
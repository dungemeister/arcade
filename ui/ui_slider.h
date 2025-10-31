#pragma once
#include "ui_widget.h"
#include <vector>

template<typename T>
class UISlider: public UIWidget{
public:
    // UISlider()
    UISlider(class UILayout* layout);
    ~UISlider() = default;
    void Update(float deltatime) override;
    void Draw() override;
    void HandleEvent(const SDL_Event& event) override;
    void SetFloatRange(float start, float stop, float step);

private:
    std::vector<T> m_range;
};

//Template file .tpp
#include "ui_slider.cpp"
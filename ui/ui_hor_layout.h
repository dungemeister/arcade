#pragma once
#include "ui_layout.h"

class UIHorLayout: public UILayout{
public:
    enum Alignment{
        ELeft,
        ERight,
        ECenter
    };
    enum WindowAlignment{
        EWindowLeft,
        EWindowRight,
        EWindowCenter
    };
    UIHorLayout(class Game* game);
    virtual ~UIHorLayout() = default;

    void PushBackWidget(class UIWidget* widget);
    void SetAlignment(Alignment align);
    void DrawBorder();
protected:
    float m_max_width;
    void SetWindowAlignment(WindowAlignment align);
    void UpdateWidgetsHorizontalPosition();
};
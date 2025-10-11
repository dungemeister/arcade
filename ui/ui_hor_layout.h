#pragma once
#include "ui_layout.h"

class UIHorLayout: public UILayout{
public:
    enum Alignment{
        Left,
        Right,
        Center
    };
    UIHorLayout(class Game* game);
    virtual ~UIHorLayout() = default;

    void PushBackWidget(class UIWidget* widget);
    void SetAlignment(Alignment align);
protected:

};
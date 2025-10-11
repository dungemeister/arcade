#pragma once
#include "types.h"
#include "ui_widget.h"
#include <vector>

class UILayout{
public:
    enum State{
        EActive,
        EClosed,
    };
    UILayout(class Game* game);
    virtual ~UILayout();
    void SetState(UILayout::State state) { m_state = state; }
    UILayout::State GetState() const { return m_state; }

    Game* GetGame() const { return m_game; }

    virtual void Update(float deltatime) {};
    virtual void Draw() {};
    virtual void ProcessInput(const bool* keys) {};
    virtual void HandleEvent(const SDL_Event&) {};

    void AddWidget(UIWidget* widget){ m_widgets.push_back(widget); }
    void RemoveWidget(UIWidget* widget);
protected:
    Game* m_game;
    SDL_FRect m_rect;
    UILayout::State m_state;
    std::vector<UIWidget*> m_widgets;
};
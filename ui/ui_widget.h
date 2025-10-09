#pragma once
#include "types.h"
#include "SDL3/SDL.h"

class UIWidget{
public:
    typedef SDL_FRect UISize;
    UIWidget(class UILayout*);
    UIWidget();
    virtual ~UIWidget() = default;

    void        SetLayout(UILayout* layout) { m_layout = layout; }
    UILayout*   GetLayout() const           { return m_layout; }

    void    SetSize(const UISize& size)     { m_size = size; }
    UISize  GetSize() const                 { return m_size; }
    UISize  GetSizePadding() const          { return m_size_padding; }
    
    void SetPosition(const SDL_FPoint& pos) { m_size.x = pos.x; m_size.y = pos.y; }

    bool    IsHovered() const               { return m_hovered;}
    void    SetHovered(bool state)          { m_hovered = state; }

    virtual bool СontainsPoint(const SDL_FPoint& point) const {
        return SDL_PointInRectFloat(&point, &m_size);
    }
    
    virtual void Update(float deltatime) {}
    virtual void Draw() {}
    virtual void HandleEvent(const SDL_Event& event) {}
protected:
    class UILayout* m_layout;
    UISize m_size;
    UISize m_size_padding;

    bool m_hovered;
};
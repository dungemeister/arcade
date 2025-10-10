#pragma once
#include "ui_layout.h"
#include "ui_text.h"
#include <string>
#include <vector>
#include "SDL3/SDL.h"

class UIStatisticsHud: public UILayout{
public:
    UIStatisticsHud(class Game* game);
    void Draw() override;
    void Update(float deltatime) override;
    
    void UpdateFps();
private:
    //FPS
    UIText* m_fps;
    int m_frame_counter;
    float m_update_time;
    float m_last_time;
    float m_frame_time;
    float m_current_fps;
};
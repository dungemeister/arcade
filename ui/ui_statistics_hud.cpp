#include "ui_statistics_hud.h"
#include "game.h"
#include <sstream>
#include <iomanip>

UIStatisticsHud::UIStatisticsHud(Game* game)
    :UILayout(game)
    ,m_frame_counter(0)
    ,m_update_time(0.f)
    ,m_last_time(0.f)
    ,m_frame_time(0.f)
{
    m_fps = new UIText(this);
    m_fps->SetPosition({0, 0});
    UpdateFps();

}

void UIStatisticsHud::Draw(){
    m_fps->Draw();
}

void UIStatisticsHud::Update(float deltatime){
    m_frame_counter++;
    m_update_time += deltatime;

    // Обновляем FPS каждые 0.5 секунды
    if (m_update_time >= 0.5f) {
        Uint64 currentTime = SDL_GetTicks();
        float elapsedSeconds = (currentTime - m_last_time) / 1000.0f;
        
        m_current_fps = m_frame_counter / elapsedSeconds;
        m_frame_time = (elapsedSeconds / m_frame_counter) * 1000.0f; // в миллисекундах
        
        m_frame_counter = 0;
        m_last_time = currentTime;
        m_update_time = 0.0f;
        
        UpdateFps();
        // updateTexts();
        // updateColors();
    }
}

void UIStatisticsHud::UpdateFps(){
    std::stringstream stream;
    stream << std::fixed << std::setprecision(0) << "FPS: ";
    if(m_current_fps <= 0.f) 
        stream << "0";
    else
        stream  << m_current_fps;
    m_fps->SetText(stream.str());
}
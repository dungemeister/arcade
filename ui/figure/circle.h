#include "SDL3/SDL.h"
#include <vector>
#include <cmath>

class CircleOutline{
public:
    static void DrawCircle(SDL_Renderer* renderer, int centerX, int centerY, float radius, SDL_Color color) {
        const int segments = 128; // Чем больше сегментов, тем глаже окружность
        std::vector<SDL_FPoint> points;
        
        // Создаем точки окружности
        for (int i = 0; i <= segments; i++) {
            float angle = 2.0f * M_PI * i / segments;
            float x = centerX + radius * cosf(angle);
            float y = centerY + radius * sinf(angle);
            points.push_back({x, y});
        }
        
        // Устанавливаем цвет
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        
        // Рисуем соединенные линии
        SDL_RenderLines(renderer, points.data(), points.size());
    }
};
#pragma once

#include "third_party/stb_vorbis.h"

#include "enemy.h"
#include "ship.h"
#include "asteroid.h"
#include "sprite_component.h"
#include "ui_hud.h"
#include "ui_main_menu.h"
#include "ui_statistics_hud.h"
#include "ui_settings.h"
#include "spawn_component.h"

#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <thread>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <pulse/simple.h>

class Game{
public:
    Game():
    m_current_ticks(0)
    ,m_window(nullptr)
    ,m_renderer(nullptr)
    ,m_width(1920.f)
    ,m_height(1080.f)
    ,m_state(GameState::MainMenu)
    ,m_running(true)
    ,m_server(nullptr)
    ,m_music_play(false)
    ,m_fps(0.f)
    ,m_font_size(24)
    ,m_statistics_hud(nullptr)
    ,m_settings_ui(nullptr)
    ,m_main_menu(nullptr)
    ,m_hud_ui(nullptr)
    ,m_spawner_actor(nullptr)
    ,m_updating_actors(false)
    {
        
        auto res = Initialize();
        m_sprites.reserve(10);
    }

    enum GameState{
        MainMenu,
        Settings,
        Gameplay,
        PauseMenu,
        GameOver,
    };

    float GetWindowWidth() const { return m_width; }
    float GetWindowHeight() const { return m_height; }

    void SetRunning(bool state) { m_running = state; }
    
    bool Initialize();
    void InitPulseAudio();

    void StartGame();
    void EndGame();

    void StartSettingsUI();
    void EndSettingsUI();

    void SetState(Game::GameState state) { m_state = state; }
    Game::GameState GetState() const { return m_state; }

    SDL_Texture* LoadTexture(const char* fileName);
    SDL_Texture* GetTexture(const std::string& filename);
    void UnloadTextures();

    void LoadBackground();
    void UnloadBackground();

    void LoadMainMenu();
    void UnloadMainMenu();

    void LoadStatisticsHud();
    void UnloadStatisticsHud();

    void LoadHud();
    void UnloadHud();

    void LoadData();
    void UnloadData();

    void LoadSettingsUI();
    void UnloadSettingsUI();

    void Shutdown(){
        UnloadData();
        UnloadBackground();

        StopMusicThread();
        TTF_Quit();
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }


    Game* GetGame() { return this; }
    SDL_Window* GetWindow() { return m_window; }
    
    void SetFontSize(int size);
    std::vector<Ship*>& GetShips() { return m_ships; }
    Vector2 GetShipPosition() {
        if(!m_ships.empty()) return m_ships[0]->GetPosition();
        return {};
    }

    std::vector<Enemy*>& GetEnemies() { return m_enemies; }

    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);

    void AddSprite(SpriteComponent* sprite);
    void RemoveSprite(SpriteComponent* sprite);

    void AddEnemy(Enemy* enemy);
    void RemoveEnemy(Enemy* enemy);
    void RemoveAllEnemies();

    void AddShip(Ship* ship);
    void RemoveShip(Ship* ship);
    void RemoveAllShips();

    void AddUI(UILayout* ui);
    void RemoveUI(UILayout* ui);
    void RemoveAllUI();

    void run();
    void ProcessInput();
    void UpdateGame();
    void ProcessOutput();
    
    void KilledEnemy();
    int GetShipHealth() const;
    int GetShipEnergy() const;
    SDL_Renderer* GetRenderer() const { return m_renderer; }

    void PlayAudioThread(std::string filename);
    void StopMusicThread();

    void SwitchState(GameState state);
    void HandleActors(float deltatime);
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    int m_width;
    int m_height;

    TTF_Font* m_info_font;
    int m_font_size;

    bool m_running;
    uint64_t m_current_ticks;
    GameState m_state;
    float m_fps;

    UIMainMenu* m_main_menu;
    UIStatisticsHud* m_statistics_hud;
    UISettings* m_settings_ui;
    UIHud* m_hud_ui;

    std::unordered_map<std::string, SDL_Texture*> m_textures;
    bool m_updating_actors;
    std::vector<Actor*> m_pending_actors;
    std::vector<Actor*> m_actors;
    std::vector<Actor*> m_dead_actors;
    std::vector<SpriteComponent*> m_sprites;
    std::vector<Ship*> m_ships;
    std::vector<Asteroid*> m_asteroids;
    std::vector<Enemy*> m_enemies;
    std::vector<UILayout*> m_ui_layouts;
    Actor* m_spawner_actor;

    std::unordered_map<GameState, std::vector<UILayout*>> m_lays;
    std::thread m_music_thr;
    bool m_music_play;
    pa_simple* m_server;
    int16_t m_buffer[4096];


};

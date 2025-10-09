#include "game.hpp"
#include "background_sprite_component.h"
#include "projectile.h"
#include "follow_projectile.h"
#include "asteroid.h"
#include "enemy.h"
#include "random.h"

#include "pulse/simple.h"
#include "pulse/pulseaudio.h"
#include "pulse/error.h"
#include "assert.h"

#include "third_party/stb_vorbis.h"

bool Game::Initialize(){
    //Init SDL
    auto res = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if(!res){
        SDL_Log("Failed to init SDL3");
        return false;
    }
    res = TTF_Init();
    if(!res){
        SDL_Log("Failed to init SDL3_TTF");
        return false;
    }
    m_info_font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", m_font_size); // Укажите путь к шрифту

    if(!m_info_font){
        SDL_Log("%s", SDL_GetError());
    }
    m_window = SDL_CreateWindow("Hybrid Ping-Pong", m_width, m_height, 0);
    if(!m_window){
        SDL_Log("Failed to create SDL3 window");
        return false;
    }
    m_renderer = SDL_CreateRenderer(m_window, NULL);
    if(!m_renderer){
        SDL_Log("Failed to create SDL3 renderer");
    }
    //Init Audio
    InitPulseAudio();

    LoadBackground();
    LoadMainMenu();
    m_current_ticks = SDL_GetTicks();
    return true;
}

void Game:: SetFontSize(int size){
    if(m_font_size == size) return;

    m_font_size = size;
    m_info_font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", size);
    if(!m_info_font){
        SDL_Log("%s", SDL_GetError());
    }
}

void Game::InitPulseAudio(){
    pa_sample_spec ss = {
        .format = PA_SAMPLE_S16LE,
        .rate = 44100,
        .channels = 2
    };
    int error;
    m_server = pa_simple_new(NULL, "Game Playback", PA_STREAM_PLAYBACK, NULL, "The Game", &ss, NULL, NULL, &error);
    if(!m_server){
        SDL_Log("Failed to init pulseaudio server connection %s", pa_strerror(error));
        return;
    }
    std::string sound_filename = "Assets/Sounds/main_theme.ogg";
    stb_vorbis* m_main_theme = stb_vorbis_open_filename(sound_filename.c_str(), NULL, NULL);
    stb_vorbis_seek_start(m_main_theme);

    // assert(ss.rate == m_main_theme->sample_rate);
    // assert(ss.channels == m_main_theme->channels);

    if(!m_main_theme){
        SDL_Log("Failed to open ogg file %s", sound_filename.c_str());
        return;
    }

    m_music_play = false;
    m_music_thr = std::thread([this, m_main_theme, ss](){
        int error;
        while(m_music_play){
            while(m_music_play && m_state == GameState::Active && stb_vorbis_get_samples_short_interleaved(m_main_theme, ss.channels, m_buffer, sizeof(m_buffer) / sizeof(int16_t))){
                auto res = pa_simple_write(m_server, m_buffer, sizeof(m_buffer), &error);
            }
        }
    });
    
}

void Game::StartGame(){
    UnloadMainMenu();
    SetState(GameState::Active);
    LoadData();
    LoadHud();
}

void Game::EndGame(){
    SetState(GameState::MainMenu);
    UnloadData();
    UnloadHud();
    LoadMainMenu();
}

void Game::StopMusicThread(){
    m_music_play = false;
    if(m_music_thr.joinable()) m_music_thr.join();
}

SDL_Texture* Game::LoadTexture(const char* fileName){
    SDL_Surface* surf = IMG_Load(fileName);

    if(!surf){
        SDL_Log("Failed to load texture file %s", fileName);
        return nullptr;
    }

    SDL_Texture* text = SDL_CreateTextureFromSurface(m_renderer, surf);
    if(!text){
        SDL_Log("Failed to create texture from surface");
        return nullptr;
    }
    return text;   
}

SDL_Texture* Game::GetTexture(const std::string& filename){
    SDL_Texture* text = nullptr;
    auto iter = m_textures.find(filename);
    if(iter != m_textures.end()){
        text = iter->second;
    }
    else{
        text = LoadTexture(filename.c_str());
    }
    return text;
}

void Game::LoadBackground(){
    Actor* background_actor = new Actor(this);
    background_actor->SetPosition({static_cast<float>(m_width / 2), static_cast<float>(m_height / 2)});

    BackgroundSpriteComponent* bsc = new BackgroundSpriteComponent(background_actor);
    bsc->SetScreenSize({static_cast<float>(m_width), static_cast<float>(m_height)});

    std::vector<SDL_Texture*> bg_textures = {
        GetTexture("Assets/Farback01.png"),
        GetTexture("Assets/Farback02.png")
    };
    bsc->SetBGTextures(bg_textures);
    bsc->SetScrollSpeed(-100.f);

    bsc = new BackgroundSpriteComponent(background_actor, 50);
    bsc->SetScreenSize({static_cast<float>(m_width), static_cast<float>(m_height)});
    bg_textures = {
        GetTexture("Assets/Stars.png"),
        GetTexture("Assets/Stars.png")
    };
    bsc->SetBGTextures(bg_textures);
    bsc->SetScrollSpeed(-200.f);
}

void Game::UnloadBackground(){

}

void Game::LoadMainMenu(){
    m_main_menu = new UIMainMenu(this);
}

void Game::UnloadMainMenu(){
    auto it = std::find(m_ui_screens.begin(), m_ui_screens.end(), m_main_menu);
    m_ui_screens.erase(it);
}

void Game::LoadHud(){
    UIHud* hud = new UIHud(this);
}

void Game::UnloadHud(){

}

void Game::LoadData(){

    float width = 1024.f;
    float height = 768.f;
    for(int i = 0; i < 10; i++)
        m_asteroids.emplace_back(new Asteroid(this));

    auto ship = new Ship(this);
    ship->SetPosition({100, m_height / 2});
    ship->SetScale(2.f);

    AddShip(ship);
    
    for(int i = 0; i < 1; i++)
    {
        auto enemy = new Enemy(this, "Assets/Enemy.png");
        enemy->SetPosition({static_cast<float>(m_width - 50), Random::GetFloatRange(50.f, m_height - 50.f)});
        enemy->SetScale(2.f);
        enemy->SetRotation(MyMath::Pi);

        m_enemies.push_back(enemy);

    }

}

void Game::UnloadData(){
    RemoveAllEnemies();
    RemoveAllShips();
}

void Game::AddActor(Actor* actor){
    if(m_updating_actors){
        m_pending_actors.emplace_back(actor);
    }
    else {
        m_actors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor* actor){
    auto iter = std::find(m_pending_actors.begin(), m_pending_actors.end(), actor);
    if (iter != m_pending_actors.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, m_pending_actors.end() - 1);
        m_pending_actors.pop_back();
    }

    // Is it in actors?
    iter = std::find(m_actors.begin(), m_actors.end(), actor);
    if (iter != m_actors.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, m_actors.end() - 1);
        m_actors.pop_back();
    }

}

void Game::AddSprite(SpriteComponent* sprite){
    int sprite_draw_order = sprite->GetDrawOrder();
    auto iter = m_sprites.begin();
    for(; iter != m_sprites.end(); ++iter){
        if(sprite_draw_order < (*iter)-> GetDrawOrder()){
            break;
        }
    }
    m_sprites.insert(iter, sprite);

}

void Game::RemoveSprite(SpriteComponent* sprite){
    auto iter = std::find(m_sprites.begin(), m_sprites.end(), sprite);
    m_sprites.erase(iter);
}

void Game::AddEnemy(Enemy* enemy){
    m_enemies.push_back(enemy);
}

void Game::RemoveEnemy(Enemy* enemy){
    auto it = std::find(m_enemies.begin(), m_enemies.end(), enemy);
    m_enemies.erase(it);
}

void Game::RemoveAllEnemies(){
    while(!m_enemies.empty()){
        delete m_enemies.back();
    }
}

void Game::AddShip(Ship* ship){
    m_ships.push_back(ship);
}

void Game::RemoveShip(Ship* ship){
    auto it = std::find(m_ships.begin(), m_ships.end(), ship);
    m_ships.erase(it);
}

void Game::RemoveAllShips(){
    while(!m_ships.empty()){
        delete m_ships.back();
    }
}

void Game::AddUI(UILayout* ui){
    m_ui_screens.push_back(ui);
}

void Game::RemoveUI(UILayout* ui){
    auto it = std::find(m_ui_screens.begin(), m_ui_screens.end(), ui);
    m_ui_screens.erase(it);

}

void Game::run(){
    Uint32 lastTime = SDL_GetTicks();
    int frames = 0;
    Uint32 interval = 1000; // 1 секунда в мс
    while(m_running){
        Uint32 currentTime = SDL_GetTicks();
        frames++;

        if (currentTime - lastTime >= interval) {
            m_fps = static_cast<float>(frames) / (currentTime - lastTime) * 1000.0f;
            lastTime = currentTime;
            frames = 0;
        }
        ProcessInput();
        UpdateGame();
        ProcessOutput();
        
        SDL_Delay(8); // Ограничивает ~120 FPS
    }
}

void Game::ProcessInput(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_EVENT_MOUSE_MOTION:
                
                break;
            case SDL_EVENT_KEY_UP: //Key released
                if(event.key.key == SDLK_SPACE){
                    if(m_state == GameState::Active) m_state = GameState::Menu;
                    else if(m_state == GameState::Menu) m_state = GameState::Active;
                }
                if(event.key.key == SDLK_ESCAPE){
                    m_running = false;
                }
                if(event.key.key == SDLK_R){
                    UnloadData();
                }
                if(event.key.key == SDLK_N){
                    LoadData();
                }
                break;
            
            case SDL_EVENT_KEY_DOWN: //Key pressed
                break;
            
            case SDL_EVENT_QUIT:
                m_running = false;
                break;
        }
        if(m_state == Game::GameState::MainMenu && m_main_menu)
            m_main_menu->HandleEvent(event);
    }
    auto state = SDL_GetKeyboardState(NULL);
    
    m_updating_actors = true;
    for(auto actor: m_actors){
        actor->ProcessInput(state);
    }
    m_updating_actors = false;

}

void Game::UpdateGame(){
        
    float deltatime = std::min(static_cast<float>(SDL_GetTicks() - m_current_ticks) / 1000, 0.01f);
    m_current_ticks = SDL_GetTicks();
    
    if(m_state == GameState::Active){
        m_updating_actors = true;

        for(auto actor: m_actors) actor->Update(deltatime);
        m_updating_actors = false;

        for(auto pending_actor: m_pending_actors) m_actors.emplace_back(pending_actor);
        m_pending_actors.clear();


        for(auto actor: m_actors){
            if(actor->GetState() == Actor::State::Dead){
                m_dead_actors.emplace_back(actor);
            } 
        }

        for(auto actor: m_dead_actors){
            delete actor;
        }
        m_dead_actors.clear();
    }
    else if(m_state == GameState::MainMenu){
        m_main_menu->Update(deltatime);
    }

}
void Game::ProcessOutput(){
    SDL_SetRenderDrawColor(m_renderer, 0x18, 0x18, 0x18, 255);
    SDL_RenderClear(m_renderer);

    size_t projectiles_counter = 0;
    size_t ship_counter = 0;
    size_t asteroid_counter = 0;
    size_t enemy_counter = 0;
    for(auto sprite: m_sprites){
        sprite->Draw(m_renderer);
        if(dynamic_cast<Projectile*>(sprite->GetOwner())) projectiles_counter++;
        if(dynamic_cast<FollowProjectile*>(sprite->GetOwner())) projectiles_counter++;
        if(dynamic_cast<Ship*>(sprite->GetOwner())) ship_counter++;
        if(dynamic_cast<Enemy*>(sprite->GetOwner())) enemy_counter++;
        if(dynamic_cast<Asteroid*>(sprite->GetOwner())) asteroid_counter++;
    }
    
    SDL_Color color = {0xff, 128, 128, 255}; // Белый цвет
    std::string text = "FPS:" + std::to_string(static_cast<int>(m_fps));
    std::string text_counter =  " Enemy obj: "      + std::to_string(enemy_counter) +
                                " Projectile objs:" + std::to_string(projectiles_counter) +
                                " Ship objs: "      + std::to_string(ship_counter) +
                                " Asteroid objs: "  + std::to_string(asteroid_counter);
    // m_font_size - global font size
    for(auto ui: m_ui_screens){
        ui->Draw();
    }
    // RenderText(m_renderer, color, text, {m_width, 0});
    // RenderText(m_renderer, color, text_counter, {m_width, m_font_size});
    // if(m_ships.empty()&&false){

    //     RenderText(m_renderer, color, "Ну че блять доигрался?", {m_width / 2, 10 * m_font_size});
    //     m_state = GameState::Paused;
    // }
    // if(m_enemies.empty()&&false){
    //     RenderText(m_renderer, color, "Легчайшая для величайшего", {m_width / 2, 10 * m_font_size});
    //     m_state = GameState::Paused;
    // }
    SDL_RenderPresent(m_renderer);
}

void Game::PlayAudioThread(std::string filename){
    
}

bool Game::RenderText( SDL_Renderer* renderer, const SDL_Color& color,
                     const std::string& text, const Vector2& pos,
                     int font_size)
{
    //Каждый раз генерится текстура, что может быть не оптимально
    SetFontSize(font_size);
    SDL_Surface* surface = TTF_RenderText_Blended(m_info_font, text.c_str(), 0, color);
    if(!surface){
        SDL_Log("%s", SDL_GetError());
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    if(!texture){
        SDL_Log("%s", SDL_GetError());
    }
    SDL_FRect dst_fps_rect = {static_cast<float>(pos.x - surface->w), static_cast<float>(pos.y),
                            static_cast<float>(surface->w), static_cast<float>(surface->h)};
    
    SDL_DestroySurface(surface);
    
    return SDL_RenderTexture(m_renderer, texture, NULL, &dst_fps_rect);
}
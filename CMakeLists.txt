cmake_minimum_required(VERSION 3.15)
project(arcade
    VERSION 0.1.0
    LANGUAGES C CXX
    DESCRIPTION "game probe from scratch by book lessons")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O2 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-g -O2 -DDEBUG")
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3_image REQUIRED)
find_package(SDL3_ttf REQUIRED)

find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)

pkg_check_modules(LIBPULSE REQUIRED libpulse)

set(UI_DIR ui)
set(ACTORS_DIR actors)
set(COMPONENTS_DIR components)
set(MISC_DIR misc)
set(THIRD_PARTY_DIR third_party)

set(SOURCES 
            ${UI_DIR}/ui_layout.cpp
            ${UI_DIR}/ui_hor_layout.cpp
            ${UI_DIR}/ui_main_menu.cpp
            ${UI_DIR}/ui_hud.cpp
            ${UI_DIR}/ui_widget.cpp
            ${UI_DIR}/ui_button.cpp
            ${UI_DIR}/ui_text.cpp
            ${UI_DIR}/ui_statistics_hud.cpp
            ${UI_DIR}/ui_settings.cpp
            ${ACTORS_DIR}/actor.cpp
            ${ACTORS_DIR}/asteroid.cpp
            ${ACTORS_DIR}/ship.cpp
            ${ACTORS_DIR}/projectile.cpp
            ${ACTORS_DIR}/enemy_projectile.cpp
            ${ACTORS_DIR}/ship_projectile.cpp
            ${ACTORS_DIR}/follow_projectile.cpp
            ${ACTORS_DIR}/enemy.cpp
            ${COMPONENTS_DIR}/component.cpp
            ${COMPONENTS_DIR}/animated_sprite_component.cpp
            ${COMPONENTS_DIR}/background_sprite_component.cpp
            ${COMPONENTS_DIR}/circle_component.cpp
            ${COMPONENTS_DIR}/sprite_component.cpp
            ${COMPONENTS_DIR}/move_component.cpp
            ${COMPONENTS_DIR}/newtonian_move_component.cpp
            ${COMPONENTS_DIR}/asteroid_move_component.cpp
            ${COMPONENTS_DIR}/input_component.cpp
            ${COMPONENTS_DIR}/projectile_move_component.cpp
            ${COMPONENTS_DIR}/follow_move_component.cpp
            ${COMPONENTS_DIR}/spawn_component.cpp
            ${MISC_DIR}/random.cpp
            game.cpp
            ${THIRD_PARTY_DIR}/stb_vorbis.c
)
set_source_files_properties(${THIRD_PARTY_DIR}/stb_vorbis.c PROPERTIES LANGUAGE CXX)
add_executable(${PROJECT_NAME} main.cpp)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR} ${LIBPULSE_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${COMPONENTS_DIR} ${UI_DIR} ${ACTORS_DIR} ${MISC_DIR} ${THIRD_PARTY_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE pulse pulse-simple)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf SDL3::SDL3)
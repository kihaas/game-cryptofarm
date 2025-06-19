cmake_minimum_required(VERSION 3.30)
project(cryptofarm)

set(SOURCES
        scr/main.cpp
        scr/game_logic.cpp
        scr/economy.cpp
        scr/ui.cpp
        scr/textures.cpp
)
add_executable(cryptofarm ${SOURCES})

target_link_libraries(cryptofarm sfml-graphics sfml-window sfml-system sfml-audio)


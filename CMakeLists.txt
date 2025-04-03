cmake_minimum_required(VERSION 3.16)
project(aaaa)

set(CMAKE_CXX_STANDARD 17)

#add_executable(aaaa scr/main.cpp)

set(SOURCES
        scr/main.cpp
        scr/game_logic.cpp
        scr/economy.cpp
        scr/ui.cpp
        scr/textures.cpp


)

# Ищем SFML
# find_package(SFML 2.6 COMPONENTS graphics.h window system REQUIRED)

# Создаём исполняемый файл
# add_executable(MySFMLProject main.cpp)
add_executable(aaaa ${SOURCES})

# Линкуем SFML
target_link_libraries(aaaa sfml-graphics sfml-window sfml-system sfml-audio)

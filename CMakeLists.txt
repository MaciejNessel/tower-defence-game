cmake_minimum_required(VERSION 3.21)
project(tower_defence_game)

set(CMAKE_CXX_STANDARD 14)



set(SDL2_INCLUDE_DIR C:/libs/SDL/include)
set(SDL2_LIB_DIR C:/libs/SDL/lib/x64)
include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

set(SDL2_IMAGE_INCLUDE_DIR C:/libs/SDL2_image/include)
set(SDL2_IMAGE_LIB_DIR C:/libs/SDL2_image/lib/x64)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
link_directories(${SDL2_IMAGE_LIB_DIR})

set(SDL2_TTF_INCLUDE_DIR C:/libs/SDL2_ttf/include)
set(SDL2_TTF_LIB_DIR C:/libs/SDL2_ttf/lib)
include_directories(${SDL2_TTF_INCLUDE_DIR})
link_directories(${SDL2_TTF_LIB_DIR})

set(SRC sources/main.cpp
        sources/Bullet.cpp
        sources/Enemy.cpp
        sources/Engine.cpp
        sources/GameBar.cpp
        sources/Grass.cpp
        sources/Map.cpp
        sources/MapObject.cpp
        sources/Position.cpp
        sources/Road.cpp
        sources/Tower.cpp
        sources/Builder.cpp
        sources/LevelEngine.cpp
        sources/MenuScreen.cpp
        sources/SDL_Circle.cpp
        sources/WaveEngine.cpp)

add_executable(tower_defence_game ${SRC})

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image SDL2_ttf)

cmake_minimum_required(VERSION 4.0)
project(idola)

set(CMAKE_CXX_STANDARD 23)

find_package(SDL3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(SDL3_shadercross CONFIG REQUIRED)

add_library(idola STATIC)

set(SDLSHADERCROSS_DXC OFF CACHE BOOL "")

target_sources(idola
        PRIVATE
        src/game.cpp
        src/game_context.cpp
        src/graphics/shader.cpp
        src/graphics/model_loader.cpp
        src/graphics/resource_uploader.cpp
        src/graphics/blend_state.cpp
        src/graphics/rasterizer_state.cpp
)

target_sources(idola
        PRIVATE
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src
        FILES
)

target_include_directories(idola
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(idola PRIVATE SDL3::SDL3 glm::glm SDL3_shadercross::SDL3_shadercross)
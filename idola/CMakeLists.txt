cmake_minimum_required(VERSION 4.0)
project(idola)

set(CMAKE_CXX_STANDARD 23)

find_package(SDL3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glaze REQUIRED)

add_library(idola STATIC)

target_sources(idola
        PRIVATE
        src/game.cpp
        src/game_context.cpp
        src/shader.cpp
        src/model_loader.cpp
        src/resource_uploader.cpp
        src/blend_state.cpp
        src/rasterizer_state.cpp
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

target_link_libraries(idola PRIVATE SDL3::SDL3 glm::glm glaze::glaze)
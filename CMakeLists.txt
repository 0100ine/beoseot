cmake_minimum_required(VERSION 4.0)
project(beoseot)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

add_executable(beoseot
        src/main.cpp
        src/beoseot.cpp
        src/game_states/title_state.cpp
)

target_include_directories(beoseot
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

add_subdirectory("idola")

target_link_libraries(beoseot idola)
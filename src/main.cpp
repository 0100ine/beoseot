#include "beoseot.hpp"

int main(int argc, char* argv[]) {

    const idola::game_config config {
        .title = "Beoseot",
        .window_width = 1024,
        .window_height = 768,
        .window_fullscreen = false
    };

    bst::beoseot game(config, SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXBC);
    game.run();

    return 0;
}
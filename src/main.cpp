#include "beoseot.hpp"
#include "game_states/title_state.hpp"

int main(int argc, char* argv[]) {

    const idola::game_config config {
        .title = "Beoseot",
        .fixed_latency = 60,
        .window_width = 1024,
        .window_height = 768,
        .window_fullscreen = false
    };


    bst::beoseot game(config, SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXBC);
    
    auto title_state = std::make_shared<bst::title_state>(game);

    game.set_state(title_state);
    game.run();

    return 0;
}
#ifndef IDOLA_GAME_CONFIG_HPP
#define IDOLA_GAME_CONFIG_HPP

#include <string>

namespace idola {
    struct game_config {
        std::string title;
        uint fixed_latency;
        uint window_width;
        uint window_height;
        bool window_fullscreen;
    };
}

#endif //IDOLA_GAME_CONFIG_HPP
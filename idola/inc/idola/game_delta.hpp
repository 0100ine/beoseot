#ifndef BEOSEOT_GAME_DELTA_HPP
#define BEOSEOT_GAME_DELTA_HPP

#include <chrono>

namespace idola {
    struct game_delta {
        std::chrono::duration<double> delta;
    };
}

#endif //BEOSEOT_GAME_DELTA_HPP

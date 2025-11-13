#ifndef IDOLA_GAMEPAD_AXIS_HPP
#define IDOLA_GAMEPAD_AXIS_HPP

#include "gamepad_input.hpp"
#include <SDL3/SDL_gamepad.h>

namespace idola {
    struct gamepad_axis : gamepad_input {
        gamepad_axis();

        SDL_GamepadAxis axis;
    };
}

#endif //IDOLA_GAMEPAD_AXIS_HPP
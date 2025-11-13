#ifndef IDOLA_GAMEPAD_BUTTON_HPP
#define IDOLA_GAMEPAD_BUTTON_HPP

#include "gamepad_input.hpp"
#include <SDL3/SDL_gamepad.h>

namespace idola {
    struct gamepad_button : gamepad_input {
        gamepad_button();
        
        SDL_GamepadButton button;
    };
}

#endif //IDOLA_GAMEPAD_BUTTON_HPP
#ifndef IDOLA_GAMEPAD_HPP
#define IDOLA_GAMEPAD_HPP
#include <array>
#include <SDL3/SDL_gamepad.h>

namespace idola {
    class gamepad {
        gamepad(SDL_GamepadType type);
        ~gamepad() = default;

        bool is_any_pressed();

    private:
        SDL_GamepadType m_type;
        std::array<bool, SDL_GAMEPAD_AXIS_COUNT> m_axis;
        std::array<bool, SDL_GAMEPAD_BUTTON_COUNT> m_buttons;
    };
}

#endif //IDOLA_GAMEPAD_HPP
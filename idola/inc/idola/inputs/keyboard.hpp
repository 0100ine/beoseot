#ifndef IDOLA_KEYBOARD_HPP
#define IDOLA_KEYBOARD_HPP
#include "keyboard_button.hpp"
#include <SDL3/SDL_scancode.h>
#include <array>
#include <optional>

namespace idola {
    class keyboard {
    public:
        keyboard();
        ~keyboard() = default;

        void update();
        bool is_any_pressed() const;
        bool is_key_pressed(SDL_Scancode scancode) const;

        const keyboard_button& get_key(SDL_Scancode scancode);

    private:
        const bool *m_state;
        bool m_is_any_pressed;
        std::array<keyboard_button, SDL_SCANCODE_COUNT> m_buttons;
    };
}

#endif //IDOLA_KEYBOARD_HPP
#ifndef IDOLA_KEYBOARD_HPP
#define IDOLA_KEYBOARD_HPP
#include "keyboard_input.hpp"
#include <SDL3/SDL_scancode.h>
#include <array>
#include <optional>

namespace idola {
    class keyboard {
    public:
        keyboard();
        ~keyboard() = default;

        void update();
        [[nodiscard]] bool is_any_pressed() const;
        [[nodiscard]] const keyboard_input& get_any_pressed() const;
        [[nodiscard]] bool is_key_pressed(SDL_Scancode scancode) const;

        const keyboard_input& get_key(SDL_Scancode scancode);
        
    private:
        const bool *m_state;
        bool m_is_any_pressed;
        keyboard_input m_any_pressed;
        std::array<keyboard_input, SDL_SCANCODE_MODE> m_buttons;
    };
}

#endif //IDOLA_KEYBOARD_HPP
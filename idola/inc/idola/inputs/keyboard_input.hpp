#ifndef IDOLA_KEYBOARD_BUTTON_HPP
#define IDOLA_KEYBOARD_BUTTON_HPP

#include "button.hpp"
#include <SDL3/SDL_scancode.h>
#include <memory>

namespace idola {
    class keyboard;
    
    struct keyboard_input final : button {
        keyboard_input();
        keyboard_input(keyboard* parent, SDL_Scancode scancode);
        ~keyboard_input() override = default;

        [[nodiscard]] bool check_pressed() const override;

        SDL_Scancode scancode;
    private:
        keyboard* m_parent;
    };
}

#endif //IDOLA_KEYBOARD_BUTTON_HPP
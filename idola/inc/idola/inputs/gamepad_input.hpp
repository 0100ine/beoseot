#ifndef IDOLA_GAMEPAD_BUTTON_HPP
#define IDOLA_GAMEPAD_BUTTON_HPP

#include "button.hpp"
#include "gamepad.hpp"

namespace idola {
    struct gamepad_input : button {
        gamepad_input();
        ~gamepad_input() override = default;
        
    protected:
        gamepad* m_parent;
    };
}

#endif //IDOLA_GAMEPAD_BUTTON_HPP
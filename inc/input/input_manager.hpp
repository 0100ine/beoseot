#ifndef BEOSEOT_INPUT_MANAGER_HPP
#define BEOSEOT_INPUT_MANAGER_HPP

#include "input/player_input.hpp"
#include <idola/inputs/inputs.hpp>

namespace bst {

    enum PLAYER_ACTION {
        PLAYER_ACTION_FORWARD,
        PLAYER_ACTION_BACKWARD,
        PLAYER_ACTION_LEFT,
        PLAYER_ACTION_RIGHT,

        PLAYER_ACTION_COUNT
    };

    class input_manager {
    public:
        explicit input_manager(const idola::inputs& inputs);
        ~input_manager();

        void update();
        void bind_action();

    private:
        const idola::inputs& m_inputs;
        std::array<SDL_Scancode, PLAYER_ACTION_COUNT> m_keyboard_binds;
        std::array<SDL_GamepadButton, PLAYER_ACTION_COUNT> m_gamepad_binds;
    };
}

#endif //BEOSEOT_INPUT_MANAGER_HPP
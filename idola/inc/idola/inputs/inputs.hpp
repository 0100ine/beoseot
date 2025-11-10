#ifndef IDOLA_INPUTS_HPP
#define IDOLA_INPUTS_HPP

#include "idola/inputs/button.hpp"
#include <SDL3/SDL_events.h>
#include <array>

namespace idola {
    struct input_axis_state {
        float x;
        float y;
    };

    class inputs {
    public:
        inputs();
        ~inputs() = default;

        void handle_event(const SDL_Event& event);
        void consume_inputs();
        void clear();

        [[nodiscard]] const button& get_button(SDL_Scancode scancode) const;
        [[nodiscard]] const button& get_button(SDL_GamepadButton gbutton) const;

    private:
        static void update_button_state(BUTTON_STATE& state, bool pressed);

    private:
        std::array<button, SDL_SCANCODE_COUNT> m_keys;
        std::array<button, SDL_GAMEPAD_BUTTON_COUNT> m_gbuttons;
    };
}

#endif //IDOLA_INPUTS_HPP
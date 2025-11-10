#include <idola/inputs/inputs.hpp>
#include <iostream>

using namespace idola;

inputs::inputs() {
}

void inputs::handle_event(const SDL_Event& event) {
    switch (event.type) {
        // Keyboard
        case SDL_EVENT_KEY_DOWN:
            m_keys[event.key.scancode].update(true);
            break;
        case SDL_EVENT_KEY_UP:
            m_keys[event.key.scancode].update(false);
            break;

            // Mouse
        case SDL_EVENT_MOUSE_MOTION:
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            break;
        case SDL_EVENT_MOUSE_WHEEL:
            break;

        // Gamepad
        case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
            m_gbuttons[static_cast<SDL_GamepadButton>(event.gbutton.button)].update(true);
            break;
        case SDL_EVENT_GAMEPAD_BUTTON_UP:
            m_gbuttons[static_cast<SDL_GamepadButton>(event.gbutton.button)].update(false);
            break;
        case SDL_EVENT_GAMEPAD_AXIS_MOTION:
            break;

        case SDL_EVENT_GAMEPAD_ADDED:
            break;
        case SDL_EVENT_GAMEPAD_REMOVED:
            break;
    }
}

void inputs::consume_inputs() {

}

void inputs::clear() {
}

const button& inputs::get_button(const SDL_Scancode scancode) const {
    return m_keys[scancode];
}

const button& inputs::get_button(const SDL_GamepadButton gbutton) const {
    return m_gbuttons[gbutton];
}


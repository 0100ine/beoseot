#include "idola/inputs/keyboard.hpp"
#include <SDL3/SDL_keyboard.h>
#include <ranges>

using namespace idola;

keyboard::keyboard() : m_state(nullptr), m_is_any_pressed(false) {
    // This should cover most for now I guess. This is dumb as hell.
    for (int i = SDL_SCANCODE_A; i < SDL_SCANCODE_MODE; i++) {
        const auto scancode = static_cast<SDL_Scancode>(i);
        m_buttons[scancode] = keyboard_input(this, scancode);
    }
    m_any_pressed = m_buttons[SDL_SCANCODE_UNKNOWN];
}

void keyboard::update() {
    int num_keys{};
    m_state = SDL_GetKeyboardState(&num_keys);
    m_is_any_pressed = false;

    for (auto& key: m_buttons) {
        key.update();

        if (key.is_pressed()) {
            m_is_any_pressed = true;
            m_any_pressed = key;
        }
    }
}

bool keyboard::is_any_pressed() const {
    return m_is_any_pressed;
}

const keyboard_input& keyboard::get_any_pressed() const {
    return m_any_pressed;
}

bool keyboard::is_key_pressed(const SDL_Scancode scancode) const {
    return m_state[scancode];
}

const keyboard_input& keyboard::get_key(SDL_Scancode scancode) {
    return m_buttons[scancode];
}


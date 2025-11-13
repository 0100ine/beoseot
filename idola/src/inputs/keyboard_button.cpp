#include "idola/inputs/keyboard_input.hpp"
#include "idola/inputs/keyboard.hpp"

using namespace idola;

keyboard_input::keyboard_input() : scancode(SDL_SCANCODE_UNKNOWN), m_parent(nullptr) {}

keyboard_input::keyboard_input(keyboard* parent, SDL_Scancode scancode)
    : scancode(scancode), m_parent(parent)
{
    
}

bool keyboard_input::check_pressed() const {
    if (scancode == SDL_SCANCODE_UNKNOWN) return false;

    return m_parent->is_key_pressed(scancode);
}
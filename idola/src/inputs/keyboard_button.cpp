#include "idola/inputs/keyboard_button.hpp"
#include "idola/inputs/keyboard.hpp"

using namespace idola;

keyboard_button::keyboard_button() : scancode(SDL_SCANCODE_UNKNOWN), m_parent(nullptr) {}

keyboard_button::keyboard_button(keyboard* parent, SDL_Scancode scancode)
    : scancode(scancode), m_parent(parent)
{

}

bool keyboard_button::check() const {
    return m_parent->is_key_pressed(scancode);
}
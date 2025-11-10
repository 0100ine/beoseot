#include "idola/inputs/button.hpp"

using namespace idola;

void button::update(bool pressed) {
    if (pressed) {
        if (is_up()) {
            state = BUTTON_STATE::PRESSED;
        }
        else {
            state = BUTTON_STATE::HELD;
        }
    }
    else {
        if (is_up()) {
            state = BUTTON_STATE::IDLE;
        }
        else {
            state = BUTTON_STATE::RELEASED;
        }
    }
}

bool button::is_up() const {
    return state == BUTTON_STATE::RELEASED || state == BUTTON_STATE::IDLE;
}

bool button::is_down() const {
    return state == BUTTON_STATE::PRESSED || state == BUTTON_STATE::HELD;
}

bool button::is_idle() const {
    return state == BUTTON_STATE::IDLE;
}

bool button::is_held() const {
    return state == BUTTON_STATE::HELD;
}



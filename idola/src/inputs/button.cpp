#include "idola/inputs/button.hpp"

using namespace idola;

button::button() : state(BUTTON_STATE::IDLE) {

}

bool button::is_released() const {
    return state == BUTTON_STATE::RELEASED;
}

bool button::is_pressed() const {
    return state == BUTTON_STATE::PRESSED;
}

bool button::is_up() const {
    return state == BUTTON_STATE::IDLE || state == BUTTON_STATE::RELEASED;
}

bool button::is_down() const {
    return state == BUTTON_STATE::HELD || state == BUTTON_STATE::PRESSED;
}

bool button::is_idle() const {
    return state == BUTTON_STATE::IDLE;
}

bool button::is_held() const {
    return state == BUTTON_STATE::HELD;
}

void button::update() {
    if (check()) {
        if (state == BUTTON_STATE::RELEASED || state == BUTTON_STATE::IDLE) {
            state = BUTTON_STATE::PRESSED;
        }
        else {
            state = BUTTON_STATE::HELD;
        }
    }
    else {
        if (state == BUTTON_STATE::PRESSED || state == BUTTON_STATE::HELD) {
            state = BUTTON_STATE::RELEASED;
        }
        else {
            state = BUTTON_STATE::IDLE;
        }
    }
}


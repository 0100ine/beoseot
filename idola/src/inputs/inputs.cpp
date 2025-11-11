#include <idola/inputs/inputs.hpp>
#include <iostream>

using namespace idola;

inputs::inputs() : m_keyboard(std::make_unique<keyboard>()){

}

void inputs::handle_events(const SDL_Event &event) {

}

void inputs::update() {
    m_keyboard->update();
}

const std::unique_ptr<keyboard>& inputs::get_keyboard() const {
    return m_keyboard;
}

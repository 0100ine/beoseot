#include "beoseot.hpp"
#include <iostream>

using namespace bst;

beoseot::beoseot(const idola::game_config &config, const SDL_GPUShaderFormat shader_format)
    : game(config, shader_format), m_title_state(std::make_unique<title_state>(m_context))
{

}

beoseot::~beoseot() = default;

void beoseot::init() {

}

void beoseot::fixed_step(const idola::game_delta &delta) {
    m_title_state->step(delta);
}

void beoseot::step(const idola::game_delta &delta) {
    auto w_state = m_inputs->get_button(SDL_SCANCODE_W);
    switch (w_state.state) {
        case idola::BUTTON_STATE::IDLE:
            std::cout << "IDLE\n";
            break;
        case idola::BUTTON_STATE::RELEASED:
            std::cout << "RELEASED\n";
            break;
        case idola::BUTTON_STATE::PRESSED:
            std::cout << "PRESSED\n";
            break;
        case idola::BUTTON_STATE::HELD:
            std::cout << "HELD\n";
            break;
    }
}

void beoseot::draw() {
    SDL_GPUCommandBuffer* command_buffer = m_context->acquire_command_buffer();
    SDL_GPUTexture* swapchain_texture = m_context->acquire_swapchain_texture(command_buffer);

    if (swapchain_texture != nullptr) {
        m_title_state->draw(command_buffer, swapchain_texture);
    }

    SDL_SubmitGPUCommandBuffer(command_buffer);
}



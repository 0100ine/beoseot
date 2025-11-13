#include "beoseot.hpp"
#include <iostream>
#include <assert.h>

using namespace bst;

beoseot::beoseot(const idola::game_config &config, const SDL_GPUShaderFormat shader_format)
    : game(config, shader_format)
{
}

beoseot::~beoseot() = default;

void beoseot::set_state(const std::shared_ptr<game_state> &state) {
    m_current_state = state;
}


void beoseot::init() {
    
}

void beoseot::fixed_step(const idola::game_delta &delta) {
    m_current_state->step(delta);
}

void beoseot::step(const idola::game_delta &delta) {
    auto& keyboard = m_inputs->get_keyboard();
    auto& any = keyboard->get_any_pressed();

    if (keyboard->is_any_pressed()) {
        std::cout << any.scancode << std::endl;
    }
}

void beoseot::draw() {
    SDL_GPUCommandBuffer* command_buffer = m_context->acquire_command_buffer();
    SDL_GPUTexture* swapchain_texture = m_context->acquire_swapchain_texture(command_buffer);

    if (swapchain_texture != nullptr) {
        m_current_state->draw(command_buffer, swapchain_texture);
    }

    SDL_SubmitGPUCommandBuffer(command_buffer);
}
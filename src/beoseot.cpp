#include "beoseot.hpp"

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

}

void beoseot::draw() {
    SDL_GPUCommandBuffer* command_buffer = m_context->acquire_command_buffer();
    SDL_GPUTexture* swapchain_texture = m_context->acquire_swapchain_texture(command_buffer);

    if (swapchain_texture != nullptr) {
        m_title_state->draw(command_buffer, swapchain_texture);
    }

    SDL_SubmitGPUCommandBuffer(command_buffer);
}



#include "idola/game_context.hpp"

#include <memory>

#include "idola/graphics/shader.hpp"
#include <SDL3/SDL.h>

using namespace idola;

game_context::game_context(const game_config &game_config, SDL_GPUShaderFormat shader_format) : m_is_running(false) {

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initialize SDL!");
        return;
    }

    int flags = SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;
    if (game_config.window_fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }
    m_window = SDL_CreateWindow(game_config.title.c_str(), (int)game_config.window_width, (int)game_config.window_height, flags);
    if (m_window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create window!");
        return;
    }

    m_device = SDL_CreateGPUDevice(shader_format, false, nullptr);
    if (m_device == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create GPU device!");
        SDL_DestroyWindow(m_window);
        return;
    }

    if (!SDL_ClaimWindowForGPUDevice(m_device, m_window)) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to claim window for GPU device!");
        SDL_DestroyWindow(m_window);
        SDL_DestroyGPUDevice(m_device);
        return;
    }

    SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(m_window);

    m_is_running = true;
}

void game_context::handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                m_is_running = false;
        }
    }
}

void game_context::shutdown(){
    SDL_ReleaseWindowFromGPUDevice(m_device, m_window);
    SDL_DestroyWindow(m_window);
    SDL_DestroyGPUDevice(m_device);
    SDL_Quit();
}

bool game_context::is_running() const {
    return m_is_running;
}

SDL_GPUTextureFormat game_context::get_swapchain_format() const {
    return SDL_GetGPUSwapchainTextureFormat(m_device, m_window);
}

SDL_GPUCommandBuffer* game_context::acquire_command_buffer() const {
    return SDL_AcquireGPUCommandBuffer(m_device);
}

SDL_GPUTexture* game_context::acquire_swapchain_texture(SDL_GPUCommandBuffer* command_buffer) const {
    SDL_GPUTexture* texture{};
    SDL_WaitAndAcquireGPUSwapchainTexture(command_buffer, m_window, &texture, nullptr, nullptr);
    return texture;
}

resource_uploader game_context::get_resource_uploader(uint32_t size) const {
    return {m_device, size};
}

SDL_GPUShader* game_context::load_shader(const std::string& filename) const {
    return shader::load(m_device, filename);
}

SDL_GPUGraphicsPipeline *game_context::create_pipeline(const SDL_GPUGraphicsPipelineCreateInfo &create_info) const {
    return SDL_CreateGPUGraphicsPipeline(m_device, &create_info);
}

model_loader game_context::create_model_loader() const {
    return model_loader(m_device);
}


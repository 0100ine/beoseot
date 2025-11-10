
#ifndef IDOLA_GAME_CONTEXT_HPP
#define IDOLA_GAME_CONTEXT_HPP

#include "game_config.hpp"
#include "graphics/resource_uploader.hpp"
#include "graphics/model_loader.hpp"
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_events.h>
#include <string>

namespace idola {
    class game_context {
    public:
        game_context(const game_config& game_config, SDL_GPUShaderFormat shader_format);
        ~game_context() = default;

        void handle_events(const SDL_Event& event);
        void shutdown();

        [[nodiscard]] bool is_running() const;
        [[nodiscard]] SDL_GPUTextureFormat get_swapchain_format() const;

        [[nodiscard]] SDL_GPUCommandBuffer* acquire_command_buffer() const;
        [[nodiscard]] SDL_GPUTexture* acquire_swapchain_texture(SDL_GPUCommandBuffer *command_buffer) const;
        [[nodiscard]] resource_uploader get_resource_uploader(uint32_t size) const;
        [[nodiscard]] SDL_GPUShader* load_shader(const std::string &filename) const;
        [[nodiscard]] SDL_GPUGraphicsPipeline* create_pipeline(const SDL_GPUGraphicsPipelineCreateInfo &create_info) const;
        [[nodiscard]] model_loader create_model_loader() const;

    private:
        bool m_is_running;
        SDL_Window* m_window;
        SDL_GPUDevice* m_device;
    };
}

#endif //IDOLA_GAME_CONTEXT_HPP
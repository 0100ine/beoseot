#ifndef BEOSEOT_TITLE_STATE_HPP
#define BEOSEOT_TITLE_STATE_HPP

#include "game_state.hpp"
#include <SDL3/SDL_gpu.h>
#include <idola/inputs/inputs.hpp>
#include <idola/graphics/model_loader.hpp>
#include <memory>

namespace bst {
    class title_state : public game_state {
    public:
        title_state(const beoseot& game);
        ~title_state() override;

        void enter() override;
        void step(const idola::game_delta& delta) override;
        void exit() override;
        void draw(SDL_GPUCommandBuffer* command_buffer, SDL_GPUTexture* swapchain_texture) override;

    private:
        const beoseot& m_game;
        unsigned int m_model;
        float m_time;
        idola::model_loader m_loader;
        SDL_GPUGraphicsPipeline* m_pipeline;
    };
}

#endif //BEOSEOT_TITLE_STATE_HPP
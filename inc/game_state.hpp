#ifndef BEOSEOT_GAME_STATE_HPP
#define BEOSEOT_GAME_STATE_HPP

#include <SDL3/SDL_gpu.h>

#include "idola/game_delta.hpp"

namespace bst {
    class game_state {
    public:
        virtual ~game_state() = default;
        
        virtual void enter() = 0;
        virtual void step(const idola::game_delta& delta) = 0;
        virtual void exit() = 0;
        virtual void draw(SDL_GPUCommandBuffer* command_buffer, SDL_GPUTexture* swapchain_texture) = 0;
    };
}

#endif //BEOSEOT_GAME_STATE_HPP
#ifndef IDOLA_GAME_HPP
#define IDOLA_GAME_HPP

#include "game_config.hpp"
#include "game_context.hpp"
#include "game_delta.hpp"
#include "inputs/inputs.hpp"
#include <SDL3/SDL_gpu.h>
#include <memory>

namespace idola {
    class game {
    public:
        game(game_config game_config, SDL_GPUShaderFormat shaderFormat);

        virtual ~game() = default;

        void run();

    protected:
        virtual void init() = 0;
        virtual void fixed_step(const game_delta& delta) = 0;
        virtual void step(const game_delta& delta) = 0;
        virtual void draw() = 0;

    protected:
        game_config m_config;
        double m_total_time;
        std::unique_ptr<game_context> m_context;
        std::unique_ptr<inputs> m_inputs;
    };
}

#endif //IDOLA_GAME_HPP
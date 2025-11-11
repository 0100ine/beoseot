#include "idola/game.hpp"
#include <utility>
#include <SDL3/SDL.h>

using namespace idola;

game::game(game_config game_config, SDL_GPUShaderFormat shaderFormat)
    : m_config(std::move(game_config)), m_total_time(0), m_context(std::make_unique<game_context>(m_config, shaderFormat)), m_inputs(std::make_unique<inputs>())
{

}

void game::run() {

    if (m_context->is_running()) {

        // Base variables for fixed step
        double t = 0.0;
        const double dt = 1.0 / m_config.fixed_latency;
        const double seconds_per_count = 1.0 / static_cast<double>(SDL_GetPerformanceFrequency());
        const Uint64 counter_base = SDL_GetPerformanceCounter();

        Uint64 counter_prev = SDL_GetPerformanceCounter();
        double accumulator = 0.0f;

        init();

        while (m_context->is_running()) {
            const Uint64 counter_now = SDL_GetPerformanceCounter();
            const Uint64 counter_delta = counter_now - counter_prev;
            m_total_time = static_cast<double>(counter_now - counter_base) * seconds_per_count;

            double frame_time = static_cast<double>(counter_delta) * seconds_per_count;
            if (frame_time > 0.25) {
                frame_time = 0.25;
            }
            counter_prev = counter_now;

            accumulator += frame_time;

            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                m_context->handle_events(event);
                m_inputs->handle_events(event);
            }

            m_inputs->update();

            while (accumulator >= dt) {
                game_delta fixed_delta{.seconds = dt};
                fixed_step(fixed_delta);
                t += dt;
                accumulator -= dt;
            }

            game_delta delta{.seconds = frame_time};
            step(delta);

            draw();
        }
    }
    m_context->shutdown();
}

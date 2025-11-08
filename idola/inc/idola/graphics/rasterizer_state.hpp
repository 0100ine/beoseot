#ifndef IDOLA_RASTERIZER_STATE_HPP
#define IDOLA_RASTERIZER_STATE_HPP

#include <SDL3/SDL_gpu.h>

namespace idola::rasterizer_state {
    SDL_GPURasterizerState ccw_cull_none();
    SDL_GPURasterizerState ccw_cull_front();
    SDL_GPURasterizerState ccw_cull_back();
    SDL_GPURasterizerState cw_cull_none();
    SDL_GPURasterizerState cw_cull_front();
    SDL_GPURasterizerState cw_cull_back();
}

#endif //IDOLA_RASTERIZER_STATE_HPP
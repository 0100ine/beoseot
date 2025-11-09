#include "idola/graphics/rasterizer_state.hpp"

using namespace idola;

SDL_GPURasterizerState rasterizer_state::ccw_cull_none() {
    static SDL_GPURasterizerState state = {
        .fill_mode = SDL_GPU_FILLMODE_FILL,
        .cull_mode = SDL_GPU_CULLMODE_NONE,
        .front_face = SDL_GPU_FRONTFACE_COUNTER_CLOCKWISE
    };
    return state;
}

SDL_GPURasterizerState rasterizer_state::ccw_cull_front() {
    static SDL_GPURasterizerState state = {
        .fill_mode = SDL_GPU_FILLMODE_FILL,
        .cull_mode = SDL_GPU_CULLMODE_FRONT,
        .front_face = SDL_GPU_FRONTFACE_COUNTER_CLOCKWISE
    };
    return state;
}

SDL_GPURasterizerState rasterizer_state::ccw_cull_back() {
    static SDL_GPURasterizerState state = {
        .fill_mode = SDL_GPU_FILLMODE_FILL,
        .cull_mode = SDL_GPU_CULLMODE_BACK,
        .front_face = SDL_GPU_FRONTFACE_COUNTER_CLOCKWISE
    };
    return state;
}

SDL_GPURasterizerState rasterizer_state::cw_cull_none() {
    static SDL_GPURasterizerState state = {
        .fill_mode = SDL_GPU_FILLMODE_FILL,
        .cull_mode = SDL_GPU_CULLMODE_NONE,
        .front_face = SDL_GPU_FRONTFACE_CLOCKWISE
    };
    return state;
}

SDL_GPURasterizerState rasterizer_state::cw_cull_front() {
    static SDL_GPURasterizerState state = {
        .fill_mode = SDL_GPU_FILLMODE_FILL,
        .cull_mode = SDL_GPU_CULLMODE_FRONT,
        .front_face = SDL_GPU_FRONTFACE_CLOCKWISE
    };
    return state;
}

SDL_GPURasterizerState rasterizer_state::cw_cull_back() {
    static SDL_GPURasterizerState state = {
        .fill_mode = SDL_GPU_FILLMODE_FILL,
        .cull_mode = SDL_GPU_CULLMODE_BACK,
        .front_face = SDL_GPU_FRONTFACE_CLOCKWISE
    };
    return state;
}

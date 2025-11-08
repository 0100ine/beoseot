#ifndef IDOLA_BLEND_STATE_HPP
#define IDOLA_BLEND_STATE_HPP

#include <SDL3/SDL_gpu.h>

namespace idola::blend_state {
    SDL_GPUColorTargetBlendState none();
    SDL_GPUColorTargetBlendState opaque();
    SDL_GPUColorTargetBlendState premultiplied_alpha_blend();
    SDL_GPUColorTargetBlendState non_premultiplied_alpha_blend();
}

#endif //IDOLA_BLEND_STATE_HPP
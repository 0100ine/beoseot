#ifndef IDOLA_SHADER_HPP
#define IDOLA_SHADER_HPP

#include <SDL3/SDL_gpu.h>
#include <string>

namespace idola::shader {
    struct info {
        unsigned int samplers;
        unsigned int storage_textures;
        unsigned int storage_buffers;
        unsigned int uniform_buffers;
    };

    SDL_GPUShader* load(SDL_GPUDevice* device, const std::string& filename);
}

#endif //IDOLA_SHADER_HPP
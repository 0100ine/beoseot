#include "idola/graphics/shader.hpp"
#include <glaze/glaze.hpp>
#include <SDL3/SDL_log.h>

using namespace idola;

SDL_GPUShader* shader::load(SDL_GPUDevice* device, const std::string& filename) {
    SDL_GPUShaderStage stage{};
    if (SDL_strstr(filename.c_str(), ".vert")) {
        stage = SDL_GPU_SHADERSTAGE_VERTEX;
    }
    else if (SDL_strstr(filename.c_str(), ".frag")) {
        stage = SDL_GPU_SHADERSTAGE_FRAGMENT;
    }
    else {
        return nullptr;
    }

    size_t code_size{};
    void* code = SDL_LoadFile((filename + ".spv").c_str(), &code_size);
    if (code == nullptr) {
        SDL_Log("Failed to load shader: %s", SDL_GetError());
        return nullptr;
    }

    info i{};
    if (auto ec = glz::read_file_json<glz::opts{.error_on_unknown_keys = false}>(i, filename + ".json", std::string{})) {
        SDL_Log("Failed to read json for shader: %s", filename.c_str());
        return nullptr;
    }

    SDL_GPUShaderCreateInfo info{};
    info.code = static_cast<const Uint8*>(code);
    info.code_size = code_size;
    info.format = SDL_GPU_SHADERFORMAT_SPIRV;
    info.stage = stage;
    info.entrypoint = "main";
    info.num_samplers = i.samplers;
    info.num_storage_textures = i.storage_textures;
    info.num_storage_buffers = i.storage_buffers;
    info.num_uniform_buffers = i.uniform_buffers;

    SDL_GPUShader* shader = SDL_CreateGPUShader(device, &info);
    SDL_free(code);
    if (shader == nullptr) {
        SDL_Log("Failed to load shader: %s", SDL_GetError());
        return nullptr;
    }
    return shader;
}
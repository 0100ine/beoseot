#include "idola/graphics/shader.hpp"
#include <SDL3/SDL_log.h>
#include <SDL3_shadercross/SDL_shadercross.h>

using namespace idola;

SDL_GPUShader* shader::load(SDL_GPUDevice* device, const std::string& filename) {
    SDL_ShaderCross_ShaderStage stage{};
    if (SDL_strstr(filename.c_str(), ".vert")) {
        stage = SDL_SHADERCROSS_SHADERSTAGE_VERTEX;
    }
    else if (SDL_strstr(filename.c_str(), ".frag")) {
        stage = SDL_SHADERCROSS_SHADERSTAGE_FRAGMENT;
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

    SDL_ShaderCross_SPIRV_Info spirv_info{};
    spirv_info.bytecode = static_cast<const Uint8*>(code);
    spirv_info.bytecode_size = code_size;
    spirv_info.entrypoint = "main";
    spirv_info.shader_stage = stage;

    const SDL_ShaderCross_GraphicsShaderMetadata* metadata = SDL_ShaderCross_ReflectGraphicsSPIRV(static_cast<const Uint8*>(code), code_size, 0);
    SDL_GPUShader* shader = SDL_ShaderCross_CompileGraphicsShaderFromSPIRV(device, &spirv_info, &metadata->resource_info, 0);

    SDL_free(code);
    if (shader == nullptr) {
        SDL_Log("Failed to load shader: %s", SDL_GetError());
        return nullptr;
    }
    return shader;
}
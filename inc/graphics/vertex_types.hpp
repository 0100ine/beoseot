#ifndef BEOSEOT_VERTEX_TYPES_HPP
#define BEOSEOT_VERTEX_TYPES_HPP

#include <idola/graphics/vertex_input_state.hpp>
#include <array>

namespace bst {

    // POSITION
    struct vertex_pos final : idola::vertex_type {
        const SDL_GPUVertexAttribute* get_attributes(uint32_t* size) override {
            *size = static_cast<uint32_t>(attributes.size());
            return attributes.data();
        }

        const SDL_GPUVertexBufferDescription* get_descriptions(uint32_t* size) override {
            *size = static_cast<uint32_t>(descriptions.size());
            return descriptions.data();
        }

        static constexpr std::array<SDL_GPUVertexAttribute, 1> attributes = {
            SDL_GPUVertexAttribute {
                .location = 0,
                .buffer_slot = 0,
                .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
                .offset = 0
            }
        };

        static constexpr std::array<SDL_GPUVertexBufferDescription, 1> descriptions = {
            SDL_GPUVertexBufferDescription {
                .slot = 0,
                .pitch = sizeof(float) * 3,
                .input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX,
                .instance_step_rate = 0
            }
        };
    };

    // POSITION NORMAL
    struct vertex_pos_nrm final : idola::vertex_type  {
        const SDL_GPUVertexAttribute* get_attributes(uint32_t* size) override {
            *size = static_cast<uint32_t>(attributes.size());
            return attributes.data();
        }

        const SDL_GPUVertexBufferDescription* get_descriptions(uint32_t* size) override {
            *size = static_cast<uint32_t>(descriptions.size());
            return descriptions.data();
        }

        static constexpr std::array<SDL_GPUVertexAttribute, 1> attributes = {
            SDL_GPUVertexAttribute {
                .location = 0,
                .buffer_slot = 0,
                .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
                .offset = 0
            }
        };

        static constexpr std::array<SDL_GPUVertexBufferDescription, 1> descriptions = {
            SDL_GPUVertexBufferDescription {
                .slot = 0,
                .pitch = sizeof(float) * 3,
                .input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX,
                .instance_step_rate = 0
            }
        };
    };

    // POSITION NORMAL TEXCOORD
    struct vertex_pos_nrm_tex final : idola::vertex_type  {
        const SDL_GPUVertexAttribute* get_attributes(uint32_t* size) override {
            *size = static_cast<uint32_t>(attributes.size());
            return attributes.data();
        }

        const SDL_GPUVertexBufferDescription* get_descriptions(uint32_t* size) override {
            *size = static_cast<uint32_t>(descriptions.size());
            return descriptions.data();
        }

        static constexpr std::array<SDL_GPUVertexAttribute, 3> attributes = {
            SDL_GPUVertexAttribute { // Position
                .location = 0,
                .buffer_slot = 0,
                .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
                .offset = 0
            },
            { // Normal
                .location = 1,
                .buffer_slot = 0,
                .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
                .offset = 0
            },
            { // TexCoord
                .location = 2,
                .buffer_slot = 0,
                .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2,
                .offset = 0
            }
        };

        static constexpr std::array<SDL_GPUVertexBufferDescription, 2> descriptions = {
            SDL_GPUVertexBufferDescription {
                .slot = 0,
                .pitch = sizeof(float) * 3,
                .input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX,
                .instance_step_rate = 0
            },
            {
                .slot = 0,
                .pitch = sizeof(float) * 3,
                .input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX,
                .instance_step_rate = 0
            }
        };
    };
}

#endif //BEOSEOT_VERTEX_TYPES_HPP
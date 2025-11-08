#ifndef IDOLA_VERTEX_TYPES_HPP
#define IDOLA_VERTEX_TYPES_HPP

#include <SDL3/SDL_gpu.h>

namespace idola {

    struct float3 {
        float x, y, z;
    };
    struct float2 {
        float x, y;
    };

    // POSITION
    struct vertex_position {
        float3 position;

        static const SDL_GPUVertexElementFormat format[1];
        static const unsigned int offset[1];
    };

    // POSITION UV
    struct vertex_position_uv {
        float3 position;
        float2 uv;

        static const SDL_GPUVertexElementFormat format[2];
        static const unsigned int offset[2];
    };

    // POSITION NORMAL UV
    struct vertex_position_normal_uv {
        float3 position;
        float3 normal;
        float2 uv;

        static const SDL_GPUVertexElementFormat format[3];
        static const unsigned int offset[3];
    };

}

#endif //IDOLA_VERTEX_TYPES_HPP
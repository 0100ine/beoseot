#ifndef IDOLA_VERTEX_TYPES_HPP
#define IDOLA_VERTEX_TYPES_HPP

#include <SDL3/SDL_gpu.h>

namespace idola {
    enum class VERTEX_TYPE {
        POS,
        POS_COL,
        POS_NRM,
        POS_NRM_COL,

        POS_NRM_TEX,
        POS_NRM_TEX_COL,
        POS_NRM_TEX_COL_WEIGHTED
    };

    struct vertex_type {
        virtual ~vertex_type() = default;
        virtual std::vector<SDL_GPUVertexAttribute> get_attributes();
        virtual std::vector<SDL_GPUVertexBufferDescription> get_descriptions();
    };

    namespace vertex_input_state {

        template<typename T>
        SDL_GPUVertexInputState create_single_binding() {
            static_assert(std::is_base_of_v<vertex_type, T>,
                "T must be a derived class of vertex_type in create_single_binding<T>");
            T value{};

            const std::vector<SDL_GPUVertexAttribute> attributes = value.get_attributes();
            const std::vector<SDL_GPUVertexBufferDescription> description = value.get_descriptions();

            return {
                .vertex_buffer_descriptions = description.data(),
                .num_vertex_buffers = static_cast<uint32_t>(description.size()),
                .vertex_attributes = attributes.data(),
                .num_vertex_attributes = static_cast<uint32_t>(attributes.size()),
            };
        }
    }
}

#endif //IDOLA_VERTEX_TYPES_HPP
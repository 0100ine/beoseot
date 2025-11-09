#ifndef IDOLA_VERTEX_TYPES_HPP
#define IDOLA_VERTEX_TYPES_HPP

#include <SDL3/SDL_gpu.h>
#include <vector>

namespace idola {

    struct vertex_type {
        virtual ~vertex_type() = default;
        virtual const SDL_GPUVertexAttribute* get_attributes(uint32_t* size) = 0;
        virtual const SDL_GPUVertexBufferDescription* get_descriptions(uint32_t* size) = 0;
    };

    namespace vertex_input_state {

        template<typename T>
        SDL_GPUVertexInputState create_single_binding() {
            static_assert(std::is_base_of_v<vertex_type, T>,
                "T must be a derived class of vertex_type in create_single_binding<T>");

            T value{};
            uint32_t num_attributes;
            uint32_t num_buffers;
            const SDL_GPUVertexAttribute* attributes = value.get_attributes(&num_attributes);
            const SDL_GPUVertexBufferDescription* description = value.get_descriptions(&num_buffers);

            return {
                .vertex_buffer_descriptions = description,
                .num_vertex_buffers = num_buffers,
                .vertex_attributes = attributes,
                .num_vertex_attributes = num_attributes,
            };
        }
    }
}

#endif //IDOLA_VERTEX_TYPES_HPP
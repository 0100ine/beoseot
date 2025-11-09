#ifndef IDOLA_MODEL_LOADER_HPP
#define IDOLA_MODEL_LOADER_HPP

#include "idola/graphics/resource_uploader.hpp"
#include "idola/graphics/vertex_input_state.hpp"
#include <SDL3/SDL_gpu.h>
#include <string>
#include <map>

namespace idola {

    enum class VERTEX_ATTRIBUTE {
        POSITION = 1 << 0,
        NORMAL = 1 << 1,
        TANGENT = 1 << 2,

        TEXCOORD_0 = 1 << 3,
        TEXCOORD_1 = 1 << 4,
        TEXCOORD_2 = 1 << 5,

        COLOR_0 = 1 << 6,
        COLOR_1 = 1 << 7,

        JOINTS_0 = 1 << 8,
        JOINTS_1 = 1 << 9,
        WEIGHTS_0 = 1 << 10,
        WEIGHTS_1 = 1 << 11
    };

    inline VERTEX_ATTRIBUTE operator|(VERTEX_ATTRIBUTE a, VERTEX_ATTRIBUTE b)
    {
        return static_cast<VERTEX_ATTRIBUTE>(static_cast<int>(a) | static_cast<int>(b));
    }

    struct model {
        std::map<std::string, SDL_GPUBuffer*> vertex_buffers;
        SDL_GPUBuffer* index_buffer;
        unsigned int index_count;
    };

    struct material {
        SDL_GPUGraphicsPipeline* pipeline;
    };

    class model_loader {
    public:
        explicit model_loader(SDL_GPUDevice* device);

        unsigned int load(resource_uploader& uploader, const std::string& filename, VERTEX_TYPE vertex_type);
        void unload(unsigned int id);
        const model& get(unsigned int id);

    private:
        SDL_GPUDevice* m_device;
        unsigned int m_next_model_id;
        std::map<unsigned int, model> m_models;
        std::map<unsigned int, material> m_materials;
    };
}

#endif //IDOLA_MODEL_LOADER_HPP
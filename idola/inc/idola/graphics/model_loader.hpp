#ifndef IDOLA_MODEL_LOADER_HPP
#define IDOLA_MODEL_LOADER_HPP

#include "idola/graphics/resource_uploader.hpp"
#include <SDL3/SDL_gpu.h>
#include <string>
#include <map>

namespace idola {
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

        unsigned int load(resource_uploader& uploader, const std::string& filename);
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
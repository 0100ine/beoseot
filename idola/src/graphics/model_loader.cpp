#include "idola/graphics/model_loader.hpp"
#include "idola/graphics/vertex_input_state.hpp"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_IMPLEMENTATION
#include <ranges>
#include <tinygltf/tiny_gltf.h>
#include <SDL3/SDL_log.h>
#include <string>

using namespace idola;

model_loader::model_loader(SDL_GPUDevice* device) : m_device(device) {

}

unsigned int model_loader::load(resource_uploader& uploader, const std::string &filename, VERTEX_ATTRIBUTE flags) {
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
    std::string err;
    std::string warn;
    const bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, filename);

    if (!warn.empty()) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Warn: %s", warn.c_str());
    }
    if (!err.empty()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error: %s", err.c_str());
    }

    if (!ret) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to parse GLTF: %s", filename.c_str());
        return -1;
    }

    std::vector<uint16_t> indices;
    std::vector<unsigned char> positions;
    std::vector<unsigned char> normals;
    uint16_t index_count {0};

    const tinygltf::Scene& scene = model.scenes[model.defaultScene];

    for (const auto& mesh : model.meshes) {
        for (auto primitive : mesh.primitives) {
            const tinygltf::Accessor &idx_accessor = model.accessors[primitive.indices];
            const tinygltf::BufferView &idx_view = model.bufferViews[idx_accessor.bufferView];
            const tinygltf::Buffer &idx_buffer = model.buffers[idx_view.buffer];

            const auto* index = reinterpret_cast<const uint16_t*>(&idx_buffer.data[idx_view.byteOffset + idx_accessor.byteOffset]);
            for (size_t i = 0; i < idx_accessor.count; ++i) {
                indices.emplace_back(index_count + index[i]);
            }

            index_count += idx_accessor.count;

            // Iterate attributes
            std::map<std::string, int>::const_iterator it(primitive.attributes.begin());
            std::map<std::string, int>::const_iterator it_end(primitive.attributes.end());

            for (; it != it_end; ++it) {
                const tinygltf::Accessor &accessor = model.accessors[it->second];
                const tinygltf::BufferView &view = model.bufferViews[accessor.bufferView];
                auto span = std::span(model.buffers[view.buffer].data);

                int length {};
                int size {};

                switch (accessor.type) {
                    case TINYGLTF_TYPE_SCALAR: length = 1; break;
                    case TINYGLTF_TYPE_VEC2: length = 2; break;
                    case TINYGLTF_TYPE_VEC3: length = 3; break;
                    case TINYGLTF_TYPE_VEC4: length = 4; break;
                    default: assert(false);
                }

                switch (accessor.componentType) {
                    case TINYGLTF_COMPONENT_TYPE_FLOAT: size = sizeof(float); break;
                    case TINYGLTF_COMPONENT_TYPE_BYTE: size = sizeof(char); break;
                    case TINYGLTF_COMPONENT_TYPE_DOUBLE: size = sizeof(double); break;
                    case TINYGLTF_COMPONENT_TYPE_INT: size = sizeof(int); break;
                    case TINYGLTF_COMPONENT_TYPE_SHORT: size = sizeof(short); break;
                    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: size = sizeof(unsigned char); break;
                    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: size = sizeof(unsigned int); break;
                    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: size = sizeof(unsigned short); break;
                    default: assert(false);
                }

                auto subspan = span.subspan(view.byteOffset, accessor.count * size * length);

                if (it->first == "POSITION" && has_vertex_attribute(flags, VERTEX_ATTRIBUTE::POSITION)) {
                    positions.insert(positions.end(), subspan.begin(), subspan.end());
                }
                else if (it->first == "NORMAL" && has_vertex_attribute(flags, VERTEX_ATTRIBUTE::NORMAL)) {

                }
            }
        }
    }
    
    idola::model m{};
    m.vertex_buffers.emplace("POSITION", uploader.create_buffer(std::span(positions), SDL_GPU_BUFFERUSAGE_VERTEX));
    m.index_buffer = uploader.create_buffer(std::span(indices), SDL_GPU_BUFFERUSAGE_INDEX);
    m.index_count = index_count;
    m_models[0] = m;

    return 0;
}

void model_loader::unload(const unsigned int id) {
    if (m_models.contains(id)) {
        auto [vertex_buffers, index_buffer, index_count] = m_models[id];
        SDL_ReleaseGPUBuffer(m_device, index_buffer);

        for (const auto &val: vertex_buffers | std::views::values) {
            SDL_ReleaseGPUBuffer(m_device, val);
        }
        m_models.erase(id);
    }
}

const model& model_loader::get(const unsigned int id) {
    return m_models[id];
}

inline bool model_loader::has_vertex_attribute(VERTEX_ATTRIBUTE flags, VERTEX_ATTRIBUTE attribute) {
    return (static_cast<int>(flags) & static_cast<int>(attribute)) == static_cast<int>(attribute);
}
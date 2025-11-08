#ifndef BEOSEOT_RESOURCE_UPLOADER_HPP
#define BEOSEOT_RESOURCE_UPLOADER_HPP
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_log.h>
#include <span>
#include <vector>

namespace idola {
    struct buffer_upload {
        Uint32 offset;
        SDL_GPUBufferRegion buffer_region;
        bool cycle;
    };
    struct texture_upload {
        Uint32 offset;
        SDL_GPUTextureRegion texture_region;
        bool cycle;
    };

    class resource_uploader {
    public:
        resource_uploader(SDL_GPUDevice* device, uint32_t size);
        ~resource_uploader();

        template<typename T>
        SDL_GPUBuffer* create_buffer(std::span<T> data, SDL_GPUBufferUsageFlags usage) {
            SDL_GPUBufferCreateInfo create_info{};
            create_info.size = data.size_bytes();
            create_info.usage = usage;

            auto* buffer = SDL_CreateGPUBuffer(m_device, &create_info);
            set_buffer_data(buffer, 0, data, false);
            return buffer;
        }

        template<typename T>
        void set_buffer_data(SDL_GPUBuffer *buffer, uint32_t offset_in_elements, std::span<T> data, bool cycle) {
            const uint32_t offset_in_bytes = sizeof(T) * offset_in_elements;
            const uint32_t length_in_bytes = data.size_bytes();

            uint32_t resource_offset = copy_buffer_data(data);

            SDL_GPUBufferRegion buffer_region = {
                buffer,
                offset_in_bytes,
                length_in_bytes
            };

            m_buffer_uploads.emplace_back(resource_offset, buffer_region, cycle);
        }

        void upload();
        void upload_and_wait();
        void release();


    private:

        template<typename T>
        uint32_t copy_buffer_data(std::span<T> data) {
            const uint32_t length_in_bytes = data.size_bytes();
            check_and_resize(length_in_bytes);

            if (m_write_offset + length_in_bytes >= m_transfer_buffer_size) {
                SDL_Log("Flushing resource uploader...");
                flush(false);
            }
            
            uint32_t resource_offset = m_write_offset;
            SDL_memcpy(static_cast<T*>(m_data_ptr) + resource_offset, data.data(), length_in_bytes);
            m_write_offset += length_in_bytes;
            return resource_offset;
        }

        void check_and_resize(Uint32 data_length_bytes);
        void flush(bool wait);

    private:
        SDL_GPUDevice* m_device;
        Uint32 m_write_offset;
        Uint32 m_transfer_buffer_size;
        void* m_data_ptr;
        SDL_GPUTransferBuffer* m_transfer_buffer;
        std::vector<buffer_upload> m_buffer_uploads;
        std::vector<texture_upload> m_texture_uploads;
    };
}

#endif //BEOSEOT_RESOURCE_UPLOADER_HPP
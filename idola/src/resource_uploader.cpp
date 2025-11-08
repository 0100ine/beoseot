#include "idola/graphics/resource_uploader.hpp"

#include <tinygltf/tiny_gltf.h>

using namespace idola;

resource_uploader::resource_uploader(SDL_GPUDevice* device, uint32_t size)
    : m_device(device), m_write_offset(0), m_transfer_buffer_size(size)
{
    SDL_GPUTransferBufferCreateInfo create_info{};
    create_info.size = m_transfer_buffer_size;
    create_info.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;
    m_transfer_buffer = SDL_CreateGPUTransferBuffer(m_device, &create_info);

    m_data_ptr = SDL_MapGPUTransferBuffer(m_device, m_transfer_buffer, false);
}

resource_uploader::~resource_uploader() = default;

void resource_uploader::check_and_resize(Uint32 data_length_bytes) {
    if (m_transfer_buffer == nullptr) {
        m_transfer_buffer_size = data_length_bytes;

        SDL_GPUTransferBufferCreateInfo create_info{};
        create_info.size = m_transfer_buffer_size;
        create_info.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;
        m_transfer_buffer = SDL_CreateGPUTransferBuffer(m_device, &create_info);
        m_data_ptr = SDL_MapGPUTransferBuffer(m_device, m_transfer_buffer, false);
    }
    else if (data_length_bytes > m_transfer_buffer_size) {
        SDL_Log("Resizing resource uploader...");
        flush(false);
        SDL_UnmapGPUTransferBuffer(m_device, m_transfer_buffer);
        SDL_ReleaseGPUTransferBuffer(m_device, m_transfer_buffer);

        m_transfer_buffer_size = data_length_bytes;

        SDL_GPUTransferBufferCreateInfo create_info{};
        create_info.size = m_transfer_buffer_size;
        create_info.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;
        m_transfer_buffer = SDL_CreateGPUTransferBuffer(m_device, &create_info);

        m_data_ptr = SDL_MapGPUTransferBuffer(m_device, m_transfer_buffer, false);
    }
}

void resource_uploader::upload() {
    flush(false);
}

void resource_uploader::upload_and_wait() {
    flush(true);
}

void resource_uploader::release() {
    SDL_UnmapGPUTransferBuffer(m_device, m_transfer_buffer);
    SDL_ReleaseGPUTransferBuffer(m_device, m_transfer_buffer);
}

void resource_uploader::flush(bool wait) {
    if (m_transfer_buffer == nullptr) return;

    SDL_UnmapGPUTransferBuffer(m_device, m_transfer_buffer);
    auto* command_buffer = SDL_AcquireGPUCommandBuffer(m_device);
    auto* copy_pass = SDL_BeginGPUCopyPass(command_buffer);
    for (auto [offset, buffer_region, cycle] : m_buffer_uploads) {
        SDL_GPUTransferBufferLocation location = {
            .transfer_buffer = m_transfer_buffer,
            .offset = offset
        };
        SDL_UploadToGPUBuffer(copy_pass, &location, &buffer_region, cycle);
    }
    for (auto [offset, texture_region, cycle] : m_texture_uploads) {
        SDL_GPUTextureTransferInfo info = {
            .transfer_buffer = m_transfer_buffer,
            .offset = offset
        };
        SDL_UploadToGPUTexture(copy_pass, &info, &texture_region, cycle);
    }
    SDL_EndGPUCopyPass(copy_pass);

    if (wait) {
        auto* fence = SDL_SubmitGPUCommandBufferAndAcquireFence(command_buffer);
        SDL_WaitForGPUFences(m_device, true, &fence, 1);
        SDL_ReleaseGPUFence(m_device, fence);
    }
    else {
        SDL_SubmitGPUCommandBuffer(command_buffer);
    }

    m_data_ptr = SDL_MapGPUTransferBuffer(m_device, m_transfer_buffer, true);
    m_write_offset = 0;
    m_buffer_uploads.clear();
    m_texture_uploads.clear();
}

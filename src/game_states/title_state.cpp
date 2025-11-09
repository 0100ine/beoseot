#include "game_states/title_state.hpp"
#include "vertex_uniforms.hpp"
#include <cmath>
#include <idola/graphics/vertex_types.hpp>
#include <idola/graphics.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace bst;

title_state::title_state(const std::unique_ptr<idola::game_context>& context): m_loader(context->create_model_loader()) {
    auto uploader = context->get_resource_uploader(8192 * sizeof(float));

    m_model = m_loader.load(uploader,
        "res/meshes/test.glb",
        idola::VERTEX_ATTRIBUTE::POSITION |
        idola::VERTEX_ATTRIBUTE::NORMAL |
        idola::VERTEX_ATTRIBUTE::TEXCOORD_0);

    uploader.upload();
    uploader.release();

    SDL_GPUColorTargetDescription color_target_descriptions[1];
    color_target_descriptions[0] = {
        .format = context->get_swapchain_format(),
        .blend_state = idola::blend_state::opaque()
    };

    SDL_GPUVertexBufferDescription vertex_buffer_descriptions[3];
    vertex_buffer_descriptions[0].slot = 0;
    vertex_buffer_descriptions[0].input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX;
    vertex_buffer_descriptions[0].instance_step_rate = 0;
    vertex_buffer_descriptions[0].pitch = sizeof(float) * 3;

    vertex_buffer_descriptions[1].slot = 1;
    vertex_buffer_descriptions[1].input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX;
    vertex_buffer_descriptions[1].instance_step_rate = 0;
    vertex_buffer_descriptions[1].pitch = sizeof(float) * 3;

    vertex_buffer_descriptions[2].slot = 2;
    vertex_buffer_descriptions[2].input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX;
    vertex_buffer_descriptions[2].instance_step_rate = 0;
    vertex_buffer_descriptions[2].pitch = sizeof(float) * 2;

    SDL_GPUVertexAttribute vertex_attributes[3];
    vertex_attributes[0].buffer_slot = 0;
    vertex_attributes[0].location = 0;
    vertex_attributes[0].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3;
    vertex_attributes[0].offset = 0;

    vertex_attributes[1].buffer_slot = 1;
    vertex_attributes[1].location = 1;
    vertex_attributes[1].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3;
    vertex_attributes[1].offset = 0;

    vertex_attributes[2].buffer_slot = 2;
    vertex_attributes[2].location = 2;
    vertex_attributes[2].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2;
    vertex_attributes[2].offset = 0;

    SDL_GPUGraphicsPipelineCreateInfo create_info{};
    create_info.target_info = SDL_GPUGraphicsPipelineTargetInfo {
        .color_target_descriptions = color_target_descriptions,
        .num_color_targets = 1
    };
    create_info.multisample_state = SDL_GPUMultisampleState {
        .sample_count = SDL_GPU_SAMPLECOUNT_1
    };
    create_info.rasterizer_state = idola::rasterizer_state::ccw_cull_back();
    create_info.depth_stencil_state = SDL_GPUDepthStencilState {
        .compare_op = SDL_GPU_COMPAREOP_LESS_OR_EQUAL,
        .enable_depth_test = true
    };
    create_info.vertex_input_state = {
        .vertex_buffer_descriptions = vertex_buffer_descriptions,
        .num_vertex_buffers = 3,
        .vertex_attributes = vertex_attributes,
        .num_vertex_attributes = 3
    };
    create_info.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
    create_info.vertex_shader = context->load_shader("res/shaders/spv/solid_mesh.vert");
    create_info.fragment_shader = context->load_shader("res/shaders/spv/triangle.frag");

    m_pipeline = context->create_pipeline(create_info);
}

title_state::~title_state() = default;

void title_state::enter() {

}

void title_state::step(const idola::game_delta& delta) {
    m_time += static_cast<float>(delta.seconds);
}

void title_state::exit() {

}

void title_state::draw(SDL_GPUCommandBuffer* command_buffer, SDL_GPUTexture* swapchain_texture) {

    SDL_GPUColorTargetInfo color_info{};
    color_info.texture = swapchain_texture;
    color_info.clear_color = SDL_FColor{0, 0, 0, 255};
    color_info.load_op = SDL_GPU_LOADOP_CLEAR;
    color_info.store_op = SDL_GPU_STOREOP_STORE;

    SDL_GPURenderPass* render_pass = SDL_BeginGPURenderPass(command_buffer, &color_info, 1, nullptr);

    auto model = m_loader.get(m_model);

    SDL_BindGPUGraphicsPipeline(render_pass, m_pipeline);

    auto view_matrix = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f), glm::vec3(0, 1, 0));
    auto proj_matrix = glm::perspectiveFov(50.0f * (static_cast<float>(M_PI) / 180.0f), 1024.0f, 768.0f, 0.1f, 100.0f);

    auto model_mat_matrix = (glm::rotate(glm::translate(glm::mat4x4(1.0f), glm::vec3(0, std::cos(m_time), 0)), m_time, glm::vec3(0, 0, 1)));
    auto view_proj_matrix = proj_matrix * view_matrix;

    // Bind Vertices
    const SDL_GPUBufferBinding vertex_bindings[] {
        { .buffer = model.vertex_buffers["POSITION"], .offset = 0 },
        { .buffer = model.vertex_buffers["NORMAL"], .offset = 0 },
        { .buffer = model.vertex_buffers["TEXCOORD_0"], .offset = 0 },
    };
    SDL_BindGPUVertexBuffers(render_pass, 0, vertex_bindings, 3);

    // Bind Indices
    SDL_GPUBufferBinding index_binding{};
    index_binding.buffer = model.index_buffer;
    index_binding.offset = 0;
    SDL_BindGPUIndexBuffer(render_pass, &index_binding, SDL_GPU_INDEXELEMENTSIZE_16BIT);

    // Bind Uniforms
    uniform_view_projection vertex_uniform{};
    SDL_memcpy(vertex_uniform.model, glm::value_ptr(model_mat_matrix), sizeof(vertex_uniform.model));
    SDL_memcpy(vertex_uniform.view_proj, glm::value_ptr(view_proj_matrix), sizeof(vertex_uniform.view_proj));
    uniform_color fragment_uniform{
        .color = {1.0f, 1.0f, 1.0f, 1.0f}
    };

    SDL_PushGPUVertexUniformData(command_buffer, 0, &vertex_uniform, sizeof(vertex_uniform));
    SDL_PushGPUFragmentUniformData(command_buffer, 0, &fragment_uniform, sizeof(fragment_uniform));

    // Draw
    SDL_DrawGPUIndexedPrimitives(render_pass, model.index_count, 1, 0, 0, 0);

    SDL_EndGPURenderPass(render_pass);
}


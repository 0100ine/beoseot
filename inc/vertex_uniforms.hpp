#ifndef BEOSEOT_VERTEX_UNIFORMS_HPP
#define BEOSEOT_VERTEX_UNIFORMS_HPP

#include <glm/glm.hpp>

namespace bst {
    struct uniform_view_projection {
        float model[16];
        float view_proj[16];
    };

    struct uniform_color {
        float color[4];
    };
}

#endif //BEOSEOT_VERTEX_UNIFORMS_HPP
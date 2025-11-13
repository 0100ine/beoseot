#ifndef BEOSEOT_CAMERA_HPP
#define BEOSEOT_CAMERA_HPP

#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace bst {
    class camera {
    public:
        camera(float fov, float width, float height, glm::vec3 position, glm::quat orientation);
        ~camera() = default;

        glm::mat4x4 get_projection(float near, float far) const;
        glm::mat4x4 get_view() const;
        
    private:
        float m_fov;
        float m_width;
        float m_height;
        glm::vec3 m_position;
        glm::quat m_orientation;
    };
}

#endif //BEOSEOT_CAMERA_HPP
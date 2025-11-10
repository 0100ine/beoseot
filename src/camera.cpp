#include "camera.hpp"
#include <glm/gtx/quaternion.hpp>

using namespace bst;

camera::camera(float fov, float width, float height, const glm::vec3 position, const glm::quat orientation)
    : m_fov(fov), m_width(width), m_height(height), m_position(position), m_orientation(orientation)
{

}

glm::mat4x4 camera::get_view() const {
    return glm::translate(glm::mat4(1.0F), m_position) * glm::toMat4(m_orientation);;
}

glm::mat4x4 camera::get_projection(const float near = 0.1f, const float far = 100.0f) const {
    return glm::perspectiveFov(m_fov, m_width, m_height, near, far);
}

;

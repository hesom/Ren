#include "graphics/projection.h"
#include "glm/gtc/matrix_transform.hpp"

namespace ren
{
    Projection::Projection():
        m_fov(90.0f),
        m_nearPlane(0.1f),
        m_farPlane(100.0f),
        m_screenWidth(800),
        m_screenHeight(600)
    {

    }
    Projection::Projection(const float fov, const float nearPlane, const float farPlane, const float width, const float height):
        m_fov(fov),
        m_nearPlane(nearPlane),
        m_farPlane(farPlane),
        m_screenWidth(width),
        m_screenHeight(height)
    {
    }

    auto Projection::getProjectionMatrix() const -> glm::mat4
    {
        return glm::perspectiveFov(
            glm::radians(m_fov),
            m_screenWidth,
            m_screenHeight,
            m_nearPlane,
            m_farPlane
        );
    }
}
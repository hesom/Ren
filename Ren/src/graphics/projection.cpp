#include "graphics/projection.h"
#include "glm/gtc/matrix_transform.hpp"

namespace ren
{
    Projection::Projection():
        m_fov(90.0f),
        m_nearPlane(0.1f),
        m_farPlane(100.0f),
        m_screenHeight(600),
        m_screenWidth(800)
    {

    }
    Projection::Projection(float fov, float nearPlane, float farPlane, float width, float height):
        m_fov(fov),
        m_nearPlane(nearPlane),
        m_farPlane(farPlane),
        m_screenHeight(height),
        m_screenWidth(width)
    {
    }

    glm::mat4 Projection::getProjectionMatrix()
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
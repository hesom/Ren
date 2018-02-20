#pragma once
#include "glm/glm.hpp"

namespace ren
{
    class Projection
    {
    private:
        float m_fov;
        float m_nearPlane;
        float m_farPlane;
        float m_screenWidth;
        float m_screenHeight;
    public:
        Projection();
        Projection(float fov, float nearPlane, float farPlane, float width, float height);
        auto getProjectionMatrix() const -> glm::mat4;
    };
}
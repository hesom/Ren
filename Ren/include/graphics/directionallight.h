#pragma once
#include "glm/glm.hpp"

namespace ren
{
    class DirectionalLight
    {
    private:
        glm::vec3 m_position;
        float m_intensity;
    public:
        DirectionalLight(glm::vec3 position, float intensity=1.0f);
    };
}
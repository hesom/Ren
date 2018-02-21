#pragma once
#include "glm/glm.hpp"

namespace ren
{
    class PointLight
    {
    private:
        glm::vec3 m_position;
        glm::vec3 m_color;
        float m_attenuationLinear;
        float m_attenuationQuadratic;
    public:
        PointLight(glm::vec3 position, glm::vec3 color, float attenuationLinear = 0.0f, float attenuationQuadratic = 0.0f);
        auto getPosition() const -> const decltype(m_position)&;
        auto getColor() const -> const decltype(m_color)&;
        auto getAttenuationLinear() const -> decltype(m_attenuationLinear);
        auto getAttenuationQuadratic() const -> decltype(m_attenuationQuadratic);
    };
}
#include "graphics/pointlight.h"

namespace ren
{
    PointLight::PointLight(const glm::vec3 position, const glm::vec3 color, const float attenuationLinear, const float attenuationQuadratic) :
        m_position(position),
        m_color(color),
        m_attenuationLinear(attenuationLinear),
        m_attenuationQuadratic(attenuationQuadratic)
    {

    }

    auto PointLight::getPosition() const -> const decltype(m_position)&
    {
        return m_position;
    }
    auto PointLight::getColor() const -> const decltype(m_color)&
    {
        return m_color;
    }
    auto PointLight::getAttenuationLinear() const -> decltype(m_attenuationLinear)
    {
        return m_attenuationLinear;
    }
    auto PointLight::getAttenuationQuadratic() const -> decltype(m_attenuationQuadratic)
    {
        return m_attenuationQuadratic;
    }
}
#include "graphics/pointlight.h"

namespace ren
{
    PointLight::PointLight(const glm::vec3 position, const glm::vec3 color) :
        m_position(position),
        m_color(color)
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
}
#include "graphics/directionallight.h"

namespace ren
{
    DirectionalLight::DirectionalLight(glm::vec3 position, float intensity) :
        m_position(position),
        m_intensity(intensity)
    {

    }
}
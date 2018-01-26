#pragma once
#include "glm/glm.hpp"

namespace ren
{
    class WaterTile
    {
    private:
        glm::vec3 m_position;

    public:
        static float tile_size;
        WaterTile(float x, float y, float z);
        WaterTile(glm::vec3 position);
        auto getPosition() const -> const decltype(m_position)&;
        auto getHeight() const -> float;
    };
}
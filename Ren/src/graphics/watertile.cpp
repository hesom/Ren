#include "graphics/watertile.h"

namespace ren
{
    float WaterTile::tile_size = 10.0f;

    WaterTile::WaterTile(const float x, const float y, const float z) :
        m_position(x, y, z)
    {
    }

    WaterTile::WaterTile(const glm::vec3 position) :
        m_position(position)
    {
    }

    auto WaterTile::getPosition() const -> const decltype(m_position)&
    {
        return m_position;
    }

    auto WaterTile::getHeight() const -> float
    {
        return m_position.y;
    }
}



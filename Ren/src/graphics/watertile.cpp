#include "graphics/watertile.h"

namespace ren
{
    float WaterTile::tile_size = 10.0f;

    WaterTile::WaterTile(float x, float y, float z) :
        m_position(x, y, z)
    {
    }

    WaterTile::WaterTile(glm::vec3 position) :
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



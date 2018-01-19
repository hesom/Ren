#pragma once

#include <vector>
#include "systems/entity.h"

namespace ren
{
    class EntityManager
    {
    private:
        static std::vector<Entity> m_entities;
    };
}
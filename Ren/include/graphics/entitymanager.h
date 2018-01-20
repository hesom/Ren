#pragma once
#include <vector>
#include <string>
#include "graphics/entity.h"

namespace ren
{
    class EntityManager
    {
    private:

        static std::vector<std::shared_ptr<Entity>> m_entities;
        EntityManager();

    public:
        static size_t loadFromOBJ(std::string path);
        static std::shared_ptr<Entity> get(size_t handle);
        static void render();
    };
}

#pragma once
#include <vector>
#include <string>
#include "graphics/entity.h"
#include "graphics/directionallight.h"

namespace ren
{
    class EntityManager
    {
    private:

        static std::vector<std::shared_ptr<Entity>> m_entities;
        static std::vector<std::shared_ptr<DirectionalLight>> m_directionalLights;
        EntityManager();

    public:
        static auto loadFromOBJ(std::string path) -> std::shared_ptr<Entity>;
        static auto addDirectionalLight(glm::vec3 position, float intensity = 1.0f) -> std::shared_ptr<DirectionalLight>;
        static auto get(size_t handle) -> std::shared_ptr<Entity>;
        static auto render() -> void;
    };
}

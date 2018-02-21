#pragma once
#include <vector>
#include <string>
#include "graphics/entity.h"
#include "graphics/pointlight.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace ren
{
    class EntityManager
    {
    private:

        static std::vector<std::shared_ptr<Entity>> m_entities;
        static std::vector<std::shared_ptr<PointLight>> m_directionalLights;

        EntityManager();
        static auto processNode(aiNode *node, const aiScene *scene) -> void;

    public:
        static auto loadFromFile(std::string path) -> std::shared_ptr<Entity>;
        static auto addPointLight(glm::vec3 position, glm::vec3 color) -> std::shared_ptr<PointLight>;
        static auto get(size_t handle) -> std::shared_ptr<Entity>;
        static auto getAllEntities() -> const decltype(m_entities)&;
        static auto getAllLights() -> const decltype(m_directionalLights)&;
    };
}

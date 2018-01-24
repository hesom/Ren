#pragma once
#include <vector>
#include <string>
#include "graphics/entity.h"
#include "graphics/directionallight.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace ren
{
    class EntityManager
    {
    private:

        static std::vector<std::shared_ptr<Entity>> m_entities;
        static std::vector<std::shared_ptr<DirectionalLight>> m_directionalLights;

        EntityManager();
        static auto processNode(aiNode *node, const aiScene *scene) -> void;

    public:
        static auto loadFromFile(std::string path) -> std::shared_ptr<Entity>;
        static auto addDirectionalLight(glm::vec3 position, glm::vec3 color) -> std::shared_ptr<DirectionalLight>;
        static auto get(size_t handle) -> std::shared_ptr<Entity>;
        static auto getAllEntities() -> const decltype(m_entities)&;
        static auto getAllLights() -> const decltype(m_directionalLights)&;
    };
}

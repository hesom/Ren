#include "graphics/entitymanager.h"
#include <iostream>
#include "glm/glm.hpp"
#include "glad/glad.h"
#include "util/stb_image.h"
#include "graphics/shadermanager.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

namespace ren
{
    class Entity;

    std::vector<std::shared_ptr<Entity>> EntityManager::m_entities;
    std::vector<std::shared_ptr<PointLight>> EntityManager::m_pointLights;

    auto EntityManager::processNode(aiNode * node, const aiScene * scene) -> void
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            auto mesh = scene->mMeshes[node->mMeshes[i]];
        }
    }

    auto EntityManager::loadFromFile(std::string path) -> std::shared_ptr<Entity>
    {
        auto entity = std::make_shared<Entity>(path);
        m_entities.push_back(entity);
        return entity;
    }

    auto EntityManager::addPointLight(glm::vec3 position, glm::vec3 color, float attenuationLinear, float attenuationQuadratic) -> std::shared_ptr<PointLight>
    {
        m_pointLights.push_back(std::make_shared<PointLight>(position, color, attenuationLinear, attenuationQuadratic));
        return m_pointLights.at(m_pointLights.size()-1);
    }

    auto EntityManager::get(const size_t handle) -> std::shared_ptr<Entity>
    {
        return m_entities.at(handle);
    }

    auto EntityManager::getAllEntities() -> const decltype(m_entities)&
    {
        return m_entities;
    }

    auto EntityManager::getAllLights() -> const decltype(m_pointLights)&
    {
        return m_pointLights;
    }
}


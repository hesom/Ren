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
    std::vector<std::shared_ptr<DirectionalLight>> EntityManager::m_directionalLights;

    auto EntityManager::processNode(aiNode * node, const aiScene * scene) -> void
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        }
    }

    auto EntityManager::loadFromFile(std::string path) -> std::shared_ptr<Entity>
    {
        auto entity = std::make_shared<Entity>(path);
        m_entities.push_back(entity);
        return entity;
    }

    auto EntityManager::addDirectionalLight(glm::vec3 position, glm::vec3 color) -> std::shared_ptr<DirectionalLight>
    {
        m_directionalLights.push_back(std::make_shared<DirectionalLight>(position, color));
        return m_directionalLights.at(m_directionalLights.size()-1);
    }

    auto EntityManager::get(size_t handle) -> std::shared_ptr<Entity>
    {
        return m_entities.at(handle);
    }

    auto EntityManager::getAllEntities() -> const decltype(m_entities)&
    {
        return m_entities;
    }

    auto EntityManager::getAllLights() -> const decltype(m_directionalLights)&
    {
        return m_directionalLights;
    }
}


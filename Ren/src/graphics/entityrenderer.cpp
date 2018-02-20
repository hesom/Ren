#include "graphics/entityrenderer.h"
#include "graphics/entitymanager.h"
#include "graphics/shadermanager.h"
#include "graphics/entity.h"
#include "graphics/directionallight.h"

#define MAX_LIGHTS 16

namespace ren
{
    std::string EntityRenderer::m_defaultShader = "EntityShader";


    auto EntityRenderer::setDefaultShader(const std::string& shader) -> void
    {
        m_defaultShader = shader;
    }

    auto EntityRenderer::getDefaultShader() -> decltype(m_defaultShader)
    {
        return m_defaultShader;
    }

    auto EntityRenderer::render(const std::shared_ptr<Camera>& camera) -> void
    {
        auto shader = ShaderManager::get(m_defaultShader);
        shader->bind();
        auto entities = EntityManager::getAllEntities();
        auto directionalLights = EntityManager::getAllLights();
        const auto viewMatrix = camera->getViewMatrix();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glEnable(GL_CLIP_DISTANCE0);

        for (int i = 0; i < MAX_LIGHTS; i++) {
            if (i < directionalLights.size()) {
                shader->setUniformValue("lightPos[" + std::to_string(i) + "]", directionalLights[i]->getPosition());
                shader->setUniformValue("lightColor[" + std::to_string(i) + "]", directionalLights[i]->getColor());
            }
            else {
                shader->setUniformValue("lightPos[" + std::to_string(i) + "]", glm::vec3(0.0f));
                shader->setUniformValue("lightColor[" + std::to_string(i) + "]", glm::vec3(0.0f));
            }
        }
        
        for (const auto& entity : entities) {
            const auto modelMatrix = entity->getTransformation();
            const auto normalMatrix = glm::transpose(glm::inverse(viewMatrix*modelMatrix));
            shader->setUniformMatrix("modelMatrix", modelMatrix);
            shader->setUniformMatrix("normalMatrix", normalMatrix);
            shader->setUniformMatrix("viewMatrix", viewMatrix);
            entity->render(shader);
        }

        glDisable(GL_CLIP_DISTANCE0);
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
    }
}
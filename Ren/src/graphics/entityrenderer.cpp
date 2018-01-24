#include "graphics/entityrenderer.h"
#include "graphics/entitymanager.h"
#include "graphics/shadermanager.h"
#include "graphics/entity.h"
#include "graphics/directionallight.h"

#define MAX_LIGHTS 16

namespace ren
{
    auto EntityRenderer::render(std::shared_ptr<Camera> camera) -> void
    {
        auto entities = EntityManager::getAllEntities();
        auto directionalLights = EntityManager::getAllLights();
        glm::mat4 viewMatrix = camera->getViewMatrix();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        for (int i = 0; i < MAX_LIGHTS; i++) {
            if (i < directionalLights.size()) {
                ShaderManager::get("BasicShader")->setUniformValue("lightPos[" + std::to_string(i) + "]", directionalLights[i]->getPosition());
                ShaderManager::get("BasicShader")->setUniformValue("lightColor[" + std::to_string(i) + "]", directionalLights[i]->getColor());
            }
            else {
                ShaderManager::get("BasicShader")->setUniformValue("lightPos[" + std::to_string(i) + "]", glm::vec3(0.0f));
                ShaderManager::get("BasicShader")->setUniformValue("lightColor[" + std::to_string(i) + "]", glm::vec3(0.0f));
            }
        }
        
        for (auto entity : entities) {
            auto modelMatrix = entity->getTransformation();
            glm::mat4 normalMatrix = glm::transpose(glm::inverse(viewMatrix*modelMatrix));
            ShaderManager::get("BasicShader")->setUniformMatrix("modelMatrix", modelMatrix);
            ShaderManager::get("BasicShader")->setUniformMatrix("normalMatrix", normalMatrix);
            ShaderManager::get("BasicShader")->setUniformMatrix("viewMatrix", viewMatrix);
            ShaderManager::get("BasicShader")->setUniformValue("cameraPos", camera->getPosition());
            entity->render();
        }

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
    }
}
#include <math.h>

#include "graphics/waterrenderer.h"

#include "graphics/shadermanager.h"
#include "graphics/entitymanager.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "graphics/texture.h"
#include "util/timer.h"

#define MAX_LIGHTS 16

namespace ren
{

    std::vector<std::shared_ptr<WaterTile>> WaterRenderer::m_tiles;
    float WaterRenderer::m_waveSpeed = 0.03f;
    float WaterRenderer::m_animationTimer = 0.0f;
    GLuint WaterRenderer:: m_vao;
    GLuint WaterRenderer::m_vbo;
    std::shared_ptr<Texture> WaterRenderer::m_dudvMap;
    std::shared_ptr<Texture> WaterRenderer::m_normalMap;

    auto WaterRenderer::setUp() -> void
    {
        float vertices [] = {
            -1, -1,
            -1, 1,
            1, -1,
            1, -1,
            -1, 1,
            1, 1
        };
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), &vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(nullptr));
        glEnableVertexAttribArray(0);

        m_dudvMap = std::make_shared<Texture>();
        m_normalMap = std::make_shared<Texture>();

        m_dudvMap->fromFile("waterDUDV.png");
        m_normalMap->fromFile("waterNormal.png");
    }

    auto WaterRenderer::render(const std::shared_ptr<Camera>& camera, const std::shared_ptr<WaterFramebuffers>& fbos) -> void
    {
        m_animationTimer += m_waveSpeed * Timer::deltaTime();
        m_animationTimer = fmod(m_animationTimer, 1);
        static bool firstInvoc = true;
        if (firstInvoc) {
            setUp();
            firstInvoc = false;
        }

        auto lights = EntityManager::getAllLights();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        ShaderManager::get("WaterShader")->bind();

        ShaderManager::get("WaterShader")->setUniformValue("reflectionTexture", 0);
        ShaderManager::get("WaterShader")->setUniformValue("refractionTexture", 1);
        ShaderManager::get("WaterShader")->setUniformValue("dudvMap", 2);
        ShaderManager::get("WaterShader")->setUniformValue("normalMap", 3);
        ShaderManager::get("WaterShader")->setUniformValue("animationTimer", m_animationTimer);
        ShaderManager::get("WaterShader")->setUniformValue("cameraPos", camera->getPosition());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, fbos->getReflectionTexture());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, fbos->getRefractionTexture());
        m_dudvMap->bind(2);
        m_normalMap->bind(3);

        for (int i = 0; i < MAX_LIGHTS; i++) {
            if (i < lights.size()) {
                ShaderManager::get("WaterShader")->setUniformValue("lightPos[" + std::to_string(i) + "]", lights[i]->getPosition());
                ShaderManager::get("WaterShader")->setUniformValue("lightColor[" + std::to_string(i) + "]", lights[i]->getColor());
                ShaderManager::get("WaterShader")->setUniformValue("attenuationLinear[" + std::to_string(i) + "]", lights[i]->getAttenuationLinear());
                ShaderManager::get("WaterShader")->setUniformValue("attenuationQuadratic[" + std::to_string(i) + "]", lights[i]->getAttenuationQuadratic());
            }
            else {
                ShaderManager::get("WaterShader")->setUniformValue("lightPos[" + std::to_string(i) + "]", glm::vec3(0.0f));
                ShaderManager::get("WaterShader")->setUniformValue("lightColor[" + std::to_string(i) + "]", glm::vec3(0.0f));
                ShaderManager::get("WaterShader")->setUniformValue("attenuationLinear[" + std::to_string(i) + "]", 0.0f);
                ShaderManager::get("WaterShader")->setUniformValue("attenuationQuadratic[" + std::to_string(i) + "]", 0.0f);
            }
        }

        const auto viewMatrix = camera->getViewMatrix();
        ShaderManager::get("WaterShader")->setUniformMatrix("viewMatrix", viewMatrix);
        for (const auto& tile : m_tiles) {
            auto modelMatrix = glm::mat4(1.0f);
            const auto tilePosition = tile->getPosition();
            modelMatrix = glm::translate(modelMatrix, glm::vec3(tilePosition));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(WaterTile::tile_size));
            ShaderManager::get("WaterShader")->setUniformMatrix("modelMatrix", modelMatrix);
            glBindVertexArray(m_vao);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);

        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
    }

    auto WaterRenderer::addTile(const std::shared_ptr<WaterTile>& tile) -> void
    {
        m_tiles.push_back(tile);
    }
    auto WaterRenderer::getTiles() -> const decltype(m_tiles)&
    {
        return m_tiles;
    }
}
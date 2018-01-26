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
    float WaterRenderer::m_wave_speed = 0.03f;
    float WaterRenderer::m_animation_timer = 0.0f;
    GLuint WaterRenderer:: m_vao;
    GLuint WaterRenderer::m_vbo;
    std::shared_ptr<Texture> WaterRenderer::dudvMap;
    std::shared_ptr<Texture> WaterRenderer::normalMap;

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
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);

        dudvMap = std::make_shared<Texture>();
        normalMap = std::make_shared<Texture>();

        dudvMap->fromFile("waterDUDV.png");
        normalMap->fromFile("waterNormal.png");
    }

    auto WaterRenderer::render(std::shared_ptr<Camera> camera, std::shared_ptr<WaterFramebuffers> fbos) -> void
    {
        m_animation_timer += m_wave_speed * Timer::deltaTime();
        m_animation_timer = fmod(m_animation_timer, 1);
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
        ShaderManager::get("WaterShader")->setUniformValue("animationTimer", m_animation_timer);
        ShaderManager::get("WaterShader")->setUniformValue("cameraPos", camera->getPosition());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, fbos->getReflectionTexture());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, fbos->getRefractionTexture());
        dudvMap->bind(2);
        normalMap->bind(3);

        for (int i = 0; i < MAX_LIGHTS; i++) {
            if (i < lights.size()) {
                ShaderManager::get("WaterShader")->setUniformValue("lightPos[" + std::to_string(i) + "]", lights[i]->getPosition());
                ShaderManager::get("WaterShader")->setUniformValue("lightColor[" + std::to_string(i) + "]", lights[i]->getColor());
            }
            else {
                ShaderManager::get("WaterShader")->setUniformValue("lightPos[" + std::to_string(i) + "]", glm::vec3(0.0f));
                ShaderManager::get("WaterShader")->setUniformValue("lightColor[" + std::to_string(i) + "]", glm::vec3(0.0f));
            }
        }

        auto viewMatrix = camera->getViewMatrix();
        ShaderManager::get("WaterShader")->setUniformMatrix("viewMatrix", viewMatrix);
        for (auto tile : m_tiles) {
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            glm::vec3 tilePosition = tile->getPosition();
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

    auto WaterRenderer::addTile(std::shared_ptr<WaterTile> tile) -> void
    {
        m_tiles.push_back(tile);
    }
    auto WaterRenderer::getTiles() -> const decltype(m_tiles)&
    {
        return m_tiles;
    }
}
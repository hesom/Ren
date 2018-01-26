#include "graphics/waterrenderer.h"

#include "graphics/shadermanager.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
namespace ren
{

    std::vector<std::shared_ptr<WaterTile>> WaterRenderer::m_tiles;
    GLuint WaterRenderer:: m_vao;
    GLuint WaterRenderer::m_vbo;

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
    }

    auto WaterRenderer::render(std::shared_ptr<Camera> camera, std::shared_ptr<WaterFramebuffers> fbos) -> void
    {
        static bool firstInvoc = true;
        if (firstInvoc) {
            setUp();
        }
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        ShaderManager::get("WaterShader")->bind();

        GLuint reflectTex = fbos->getReflectionTexture();
        GLuint refractTex = fbos->getRefractionTexture();

        ShaderManager::get("WaterShader")->setUniformValue("reflectionTexture", 0);
        ShaderManager::get("WaterShader")->setUniformValue("refractionTexture", 1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, fbos->getReflectionTexture());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, fbos->getRefractionTexture());

        auto viewMatrix = camera->getViewMatrix();
        ShaderManager::get("WaterShader")->setUniformMatrix("viewMatrix", viewMatrix);
        for (auto tile : m_tiles) {
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            glm::vec3 tilePosition = tile->getPosition();
            modelMatrix = glm::translate(modelMatrix, glm::vec3(tilePosition));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(WaterTile::tile_size));
            ShaderManager::get("WaterShader")->setUniformMatrix("modelMatrix", modelMatrix);
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
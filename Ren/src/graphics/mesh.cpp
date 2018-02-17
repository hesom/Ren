#include "graphics/mesh.h"

namespace ren
{
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    {
        this->m_vertices = vertices;
        this->m_indices = indices;
        this->m_textures = textures;
    }

    Mesh::~Mesh()
    {
        this->freeBuffer();
    }

    auto Mesh::getVertices() const -> const decltype(m_vertices)&
    {
        return m_vertices;
    }

    auto Mesh::getIndices() const -> const decltype(m_indices)&
    {
        return m_indices;
    }

    auto Mesh::setupBuffer() -> void
    {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
        glEnableVertexAttribArray(3);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    auto Mesh::freeBuffer() -> void
    {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);
    }

    auto Mesh::render(std::shared_ptr<ShaderProgram> shader) -> void
    {
        bool hasNormalTex = false;
        bool hasSpecularTex = false;

        shader->setUniformValue("diffuseMap", 0);
        shader->setUniformValue("normalMap", 1);
        shader->setUniformValue("specularMap", 2);

        for (auto tex : m_textures) {
            if (tex.getType() == "texture_diffuse") {
                tex.bind(0);
            }
            if (tex.getType() == "texture_normal") {
                tex.bind(1);
                hasNormalTex = true;
            }
            if (tex.getType() == "texture_specular") {
                tex.bind(2);
                hasSpecularTex = true;
            }
        }
        if (hasNormalTex) {
            shader->setUniformValue("hasNormalTex", 1.0f);
        }
        else {
            shader->setUniformValue("hasNormalTex", 0.0f);
        }
        if (hasSpecularTex) {
            shader->setUniformValue("hasSpecularTex", 1.0f);
        }
        else {
            shader->setUniformValue("hasSpecularTex", 0.0f);
        }
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, (void*)0);
    }
}

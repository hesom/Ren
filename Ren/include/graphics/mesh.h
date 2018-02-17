#pragma once
#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "glad/glad.h"
#include "graphics/texture.h"
#include "graphics/shaderprogram.h"

namespace ren
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
        glm::vec3 tangent;
    };

    class Mesh
    {
    private:
        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;
        std::vector<Texture> m_textures;
        GLuint m_vbo, m_vao, m_ebo;
        
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        ~Mesh();
        auto getVertices() const -> const decltype(m_vertices)&;
        auto getIndices() const -> const decltype(m_indices)&;
        auto setupBuffer() -> void;
        auto freeBuffer() -> void;
        auto render(std::shared_ptr<ShaderProgram> shader) -> void;
    };
}
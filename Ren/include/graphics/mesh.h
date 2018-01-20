#pragma once
#include <vector>

#include <glm/glm.hpp>

#include "glad/glad.h"

namespace ren
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };

    class Mesh
    {
    private:
        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;
        GLuint m_vbo, m_vao, m_ebo;
        
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
        ~Mesh();
        auto getVertices() const -> const decltype(m_vertices)&;
        auto getIndices() const -> const decltype(m_indices)&;
        auto setupBuffer() -> void;
        auto freeBuffer() -> void;
        auto draw() -> void;
    };
}
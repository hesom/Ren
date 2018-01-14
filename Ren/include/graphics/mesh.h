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
        std::vector<Vertex> const &getVertices() const;
        std::vector<unsigned int> const &getIndices() const;
        void setupBuffer();
        void freeBuffer();
        void draw();
    };
}
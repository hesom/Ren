#pragma once

#include <memory>
#include "graphics/mesh.h"
#include "glm/glm.hpp"

namespace ren
{
    class Entity
    {
    private:
        std::shared_ptr<Mesh> m_mesh;
        glm::mat4 m_transformation;
    public:
        Entity(std::shared_ptr<Mesh> mesh, glm::mat4 transformation = glm::mat4(0.0f));
        void setTransformation(glm::mat4 transformation);
        void render();
    };
}

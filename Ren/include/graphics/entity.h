#pragma once

#include <memory>
#include "graphics/mesh.h"
#include "graphics/texture.h"
#include "glm/glm.hpp"

namespace ren
{
    class Entity
    {
    private:
        std::shared_ptr<Mesh> m_mesh;
        glm::mat4 m_transformation;
        std::shared_ptr<Texture> m_diffuseTex;
        std::shared_ptr<Texture> m_normalTex;
        std::shared_ptr<Texture> m_specularTex;

    public:
        Entity(
            std::shared_ptr<Mesh> mesh,
            std::shared_ptr<Texture> diffuseTex,
            std::shared_ptr<Texture> normalTex,
            std::shared_ptr<Texture> specularTex);
        auto setTransformation(glm::mat4 transformation) -> void;
        auto render() -> void;
    };
}

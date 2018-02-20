#pragma once

#include <memory>
#include "graphics/mesh.h"
#include "graphics/texture.h"
#include "glm/glm.hpp"
#include <iostream>
#include "graphics/model.h"
#include "graphics/shaderprogram.h"

namespace ren
{
    class Entity
    {
    private:
        std::shared_ptr<Model> m_model;
        glm::mat4 m_transformation{};

    public:
        explicit Entity(const std::string& path);
        auto setTransformation(glm::mat4 transformation) -> void;
        auto getTransformation() const -> const decltype(m_transformation)&;
        auto render(const std::shared_ptr<ShaderProgram>& shader) const -> void;
    };
}

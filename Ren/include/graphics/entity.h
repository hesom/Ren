#pragma once

#include <memory>
#include "graphics/mesh.h"
#include "graphics/texture.h"
#include "glm/glm.hpp"
#include <iostream>
#include "graphics/model.h"

namespace ren
{
    class Entity
    {
    private:
        std::shared_ptr<Model> m_model;
        glm::mat4 m_transformation;
        std::string m_shader;

    public:
        Entity(std::string path);
        auto setShader(std::string shader) -> void;
        auto setTransformation(glm::mat4 transformation) -> void;
        auto getTransformation() -> const decltype(m_transformation)&;
        auto render() -> void;
    };
}

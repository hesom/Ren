#include "graphics/entity.h"
namespace ren
{
    Entity::Entity(const std::string& path)
    {
        m_model = std::make_shared<Model>(path.c_str());
        m_transformation = glm::mat4(1.0f);
    }

    auto Entity::setTransformation(const glm::mat4 transformation) -> void
    {
        m_transformation = transformation;
    }

    auto Entity::getTransformation() const -> const decltype(m_transformation)&
    {
        return m_transformation;
    }

    auto Entity::render(const std::shared_ptr<ShaderProgram>& shader) const -> void
    {   
        m_model->render(shader);
    }
}



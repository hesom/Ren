#include "graphics/entity.h"
namespace ren
{
    Entity::Entity(std::string path)
    {
        m_model = std::make_shared<Model>(path.c_str());
        m_transformation = glm::mat4(1.0f);
    }

    auto Entity::setTransformation(glm::mat4 transformation) -> void
    {
        m_transformation = transformation;
    }

    auto Entity::getTransformation() -> const decltype(m_transformation)&
    {
        return m_transformation;
    }

    auto Entity::render(std::shared_ptr<ShaderProgram> shader) -> void
    {   
        m_model->render(shader);
    }
}



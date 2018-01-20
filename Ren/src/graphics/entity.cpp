#include "graphics/entity.h"
#include "graphics/shadermanager.h"
namespace ren
{
    Entity::Entity(std::shared_ptr<Mesh> mesh, glm::mat4 transformation) :
        m_mesh(mesh),
        m_transformation(transformation)
    {
    }

    void Entity::setTransformation(glm::mat4 transformation)
    {
        m_transformation = transformation;
    }

    void Entity::render()
    {
        ShaderManager::get("BasicShader")->setUniformMatrix("modelMatrix", m_transformation);
        m_mesh->draw();
    }
}



#include "graphics/entity.h"
#include "graphics/shadermanager.h"
namespace ren
{
    Entity::Entity(
        std::shared_ptr<Mesh> mesh,
        std::shared_ptr<Texture> diffuseTex,
        std::shared_ptr<Texture> normalTex,
        std::shared_ptr<Texture> specularTex) :
        m_mesh(mesh),
        m_diffuseTex(diffuseTex),
        m_normalTex(normalTex),
        m_specularTex(specularTex)
    {
        m_transformation = glm::mat4(1.0f);
    }

    void Entity::setTransformation(glm::mat4 transformation)
    {
        m_transformation = transformation;
    }

    void Entity::render()
    {
        glm::mat4 normalMatrix = glm::transpose(glm::inverse(m_transformation));
        ShaderManager::get("BasicShader")->setUniformMatrix("modelMatrix", m_transformation);
        ShaderManager::get("BasicShader")->setUniformMatrix("normalMatrix", normalMatrix);
        
        m_diffuseTex->bind(0);
        m_mesh->draw();
    }
}



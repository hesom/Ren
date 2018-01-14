#include "graphics/shadermanager.h"


namespace ren
{
    ShaderManager::ShaderManager()
    {
    }

    ShaderManager& ShaderManager::getInstance()
    {
        static ShaderManager instance;
        return instance;
    }

    ShaderManager::~ShaderManager()
    {
        for (auto entry : m_shaderMap) {
            auto shaderProgram = entry.second;
            shaderProgram->destroy();
        }
    }

    void ShaderManager::add(std::shared_ptr<ShaderProgram> shaderProgram, std::string name)
    {
        m_shaderMap[name] = shaderProgram;
    }

    void ShaderManager::add(std::string vertexShader, std::string fragmentShader, std::string name)
    {
        auto shaderProgram = std::make_shared<ShaderProgram>();
        shaderProgram->attachVertexShader(vertexShader);
        shaderProgram->attachFragmentShader(fragmentShader);
        shaderProgram->link();
        m_shaderMap[name] = shaderProgram;
    }

    void ShaderManager::add(std::string vertexShader, std::string geometryShader, std::string fragmentShader, std::string name)
    {
        auto shaderProgram = std::make_shared<ShaderProgram>();
        shaderProgram->attachVertexShader(vertexShader);
        shaderProgram->attachGeometryShader(geometryShader);
        shaderProgram->attachFragmentShader(fragmentShader);
        if (!shaderProgram->link()) {

        }
        m_shaderMap[name] = shaderProgram;
    }

    std::shared_ptr<ShaderProgram> ShaderManager::get(std::string name)
    {
        if (!m_shaderMap.count(name)) {
            return nullptr;
        }
        return m_shaderMap.at(name);
    }

    GLuint ShaderManager::getRaw(std::string name)
    {
        if (!m_shaderMap.count(name)) {
            return -1;
        }
        auto shaderProgram = m_shaderMap.at(name);
        return shaderProgram->getRaw();
    }
}


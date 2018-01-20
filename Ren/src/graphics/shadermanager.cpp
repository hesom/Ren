#include "graphics/shadermanager.h"


namespace ren
{
    std::map<std::string, std::shared_ptr<ShaderProgram>> ShaderManager::m_shaderMap;

    ShaderManager::ShaderManager()
    {
    }

    ShaderManager::~ShaderManager()
    {
        for (auto entry : m_shaderMap) {
            auto shaderProgram = entry.second;
            shaderProgram->destroy();
        }
    }

    auto ShaderManager::add(std::shared_ptr<ShaderProgram> shaderProgram, std::string name) -> void
    {
        m_shaderMap[name] = shaderProgram;
    }

    auto ShaderManager::add(std::string vertexShader, std::string fragmentShader, std::string name) -> void
    {
        auto shaderProgram = std::make_shared<ShaderProgram>();
        shaderProgram->attachVertexShader(vertexShader);
        shaderProgram->attachFragmentShader(fragmentShader);
        shaderProgram->link();
        m_shaderMap[name] = shaderProgram;
    }

    auto ShaderManager::add(std::string vertexShader, std::string geometryShader, std::string fragmentShader, std::string name) -> void
    {
        auto shaderProgram = std::make_shared<ShaderProgram>();
        shaderProgram->attachVertexShader(vertexShader);
        shaderProgram->attachGeometryShader(geometryShader);
        shaderProgram->attachFragmentShader(fragmentShader);
        if (!shaderProgram->link()) {

        }
        m_shaderMap[name] = shaderProgram;
    }

    auto ShaderManager::get(std::string name) -> std::shared_ptr<ShaderProgram>
    {
        if (!m_shaderMap.count(name)) {
            return nullptr;
        }
        return m_shaderMap.at(name);
    }

    auto ShaderManager::getRaw(std::string name) -> GLuint
    {
        if (!m_shaderMap.count(name)) {
            return -1;
        }
        auto shaderProgram = m_shaderMap.at(name);
        return shaderProgram->getRaw();
    }
}


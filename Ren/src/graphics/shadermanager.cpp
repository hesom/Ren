#include "graphics/shadermanager.h"


namespace ren
{
    std::map<std::string, std::shared_ptr<ShaderProgram>> ShaderManager::m_shaderMap;

    ShaderManager::ShaderManager()
    {
    }

    ShaderManager::~ShaderManager()
    {
        for (const auto entry : m_shaderMap) {
            auto shaderProgram = entry.second;
            shaderProgram->destroy();
        }
    }

    auto ShaderManager::add(const std::shared_ptr<ShaderProgram>& shaderProgram, const std::string& name) -> void
    {
        m_shaderMap[name] = shaderProgram;
    }

    auto ShaderManager::add(const std::string& vertexShader, const std::string& fragmentShader,
                            const std::string& name) -> void
    {
        auto shaderProgram = std::make_shared<ShaderProgram>();
        shaderProgram->attachVertexShader(vertexShader);
        shaderProgram->attachFragmentShader(fragmentShader);
        shaderProgram->link();
        m_shaderMap[name] = shaderProgram;
    }

    auto ShaderManager::add(const std::string& vertexShader, const std::string& geometryShader,
                            const std::string& fragmentShader, const std::string& name) -> void
    {
        auto shaderProgram = std::make_shared<ShaderProgram>();
        shaderProgram->attachVertexShader(vertexShader);
        shaderProgram->attachGeometryShader(geometryShader);
        shaderProgram->attachFragmentShader(fragmentShader);
        if (!shaderProgram->link()) {

        }
        m_shaderMap[name] = shaderProgram;
    }

    auto ShaderManager::get(const std::string& name) -> std::shared_ptr<ShaderProgram>
    {
        if (!m_shaderMap.count(name)) {
            return nullptr;
        }
        return m_shaderMap.at(name);
    }

    auto ShaderManager::getRaw(const std::string& name) -> GLuint
    {
        if (!m_shaderMap.count(name)) {
            return -1;
        }
        auto shaderProgram = m_shaderMap.at(name);
        return shaderProgram->getRaw();
    }
}


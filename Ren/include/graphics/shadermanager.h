#pragma once
#include <map>
#include <memory>
#include <string>
#include "graphics/shaderprogram.h"
#include "glad/glad.h"
namespace ren
{
    class ShaderManager
    {
    private:
        ShaderManager();
        static std::map<std::string, std::shared_ptr<ShaderProgram>> m_shaderMap;
    public:
        ~ShaderManager();
        ShaderManager(ShaderManager const&) = delete;
        void operator=(ShaderManager const&) = delete;
        static auto add(const std::shared_ptr<ShaderProgram>& shaderProgram, const std::string& name) -> void;
        static auto add(const std::string& vertexShader, const std::string& fragmentShader,
                        const std::string& name) -> void;
        static auto add(const std::string& vertexShader, const std::string& geometryShader, const std::string&
                        fragmentShader,
                        const std::string& name) -> void;
        static auto get(const std::string& name) -> std::shared_ptr<ShaderProgram>;
        static auto getRaw(const std::string& name) -> GLuint;
    };
}
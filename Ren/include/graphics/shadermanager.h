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
        static void add(std::shared_ptr<ShaderProgram> shaderProgram, std::string name);
        static void add(std::string vertexShader, std::string fragmentShader, std::string name);
        static void add(std::string vertexShader, std::string geometryShader, std::string fragmentShader, std::string name);
        static std::shared_ptr<ShaderProgram> get(std::string name);
        static GLuint getRaw(std::string name);
    };
}
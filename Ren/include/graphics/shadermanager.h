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
        std::map<std::string, std::shared_ptr<ShaderProgram>> m_shaderMap;
    public:
        static ShaderManager& getInstance();

        ~ShaderManager();
        ShaderManager(ShaderManager const&) = delete;
        void operator=(ShaderManager const&) = delete;
        void add(std::shared_ptr<ShaderProgram> shaderProgram, std::string name);
        void add(std::string vertexShader, std::string fragmentShader, std::string name);
        void add(std::string vertexShader, std::string geometryShader, std::string fragmentShader, std::string name);
        std::shared_ptr<ShaderProgram> get(std::string name);
        GLuint getRaw(std::string name);
    };
}
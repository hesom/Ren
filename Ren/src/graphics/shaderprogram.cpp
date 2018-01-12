#include "graphics/shaderprogram.h"
#include <vector>
#include <iostream>

bool ShaderProgram::verifyShader(GLuint shaderId)
{
    //copied from https://www.khronos.org/opengl/wiki/Shader_Compilation
    GLint success = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);

        glDeleteShader(shaderId);
        std::string log(errorLog.begin(), errorLog.end());
        std::cout << log << std::endl;
        return false;
    }
    return true;
}

bool ShaderProgram::verifyProgram(GLuint programId)
{
    GLint isLinked = 0;
    glGetProgramiv(programId, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(programId, maxLength, &maxLength, &infoLog[0]);
        glDeleteProgram(programId);
        std::string log(infoLog.begin(), infoLog.end());
        std::cout << log << std::endl;
        return false;
    }
    return true;
}

ShaderProgram::ShaderProgram()
    : m_valid(false)
{
    m_programId = glCreateProgram();
}

void ShaderProgram::attachVertexShader(std::string source)
{
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    const char *c_str = source.c_str();
    glShaderSource(vertexShaderId, 1, &c_str, nullptr);
    glCompileShader(vertexShaderId);
#ifdef _DEBUG
    verifyShader(vertexShaderId);
#endif
    glAttachShader(m_programId, vertexShaderId);
    m_attachedShaders.push_back(vertexShaderId);
}

void ShaderProgram::attachFragmentShader(std::string source)
{
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    const char *c_str = source.c_str();
    glShaderSource(fragmentShaderId, 1, &c_str, nullptr);
    glCompileShader(fragmentShaderId);
#ifdef _DEBUG
    verifyShader(fragmentShaderId);
#endif
    glAttachShader(m_programId, fragmentShaderId);
    m_attachedShaders.push_back(fragmentShaderId);
}

void ShaderProgram::attachGeometryShader(std::string source)
{
    GLuint geometryShaderId = glCreateShader(GL_GEOMETRY_SHADER);
    const char *c_str = source.c_str();
    glShaderSource(geometryShaderId, 1, &c_str, nullptr);
    glCompileShader(geometryShaderId);
#ifdef _DEBUG
    verifyShader(geometryShaderId);
#endif
    glAttachShader(m_programId, geometryShaderId);
    m_attachedShaders.push_back(geometryShaderId);
}

void ShaderProgram::link()
{
    glLinkProgram(m_programId);

#ifdef _DEBUG
    if (!verifyProgram) {
        for (auto shader : m_attachedShaders) {
            glDeleteShader(shader);
        }
    }
#endif
    for (auto shader : m_attachedShaders) {
        glDetachShader(m_programId, shader);
    }
    m_valid = true;
}

void ShaderProgram::bind()
{
    if (m_valid) {
        glUseProgram(m_programId);
    }
}

void ShaderProgram::unbind()
{
    glUseProgram(0);
}

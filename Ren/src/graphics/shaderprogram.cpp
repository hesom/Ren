#include "graphics/shaderprogram.h"
#include "glm/gtc/type_ptr.hpp"
#include <vector>
#include <iostream>

auto ShaderProgram::verifyShader(const GLuint shaderId) -> bool
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
        const std::string log(errorLog.begin(), errorLog.end());
        std::cout << log << std::endl;
        return false;
    }
    return true;
}

auto ShaderProgram::verifyProgram(const GLuint programId) -> bool
{
    GLint isLinked = 0;
    glGetProgramiv(programId, GL_LINK_STATUS, static_cast<int*>(&isLinked));
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(programId, maxLength, &maxLength, &infoLog[0]);
        glDeleteProgram(programId);
        const std::string log(infoLog.begin(), infoLog.end());
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

auto ShaderProgram::attachVertexShader(const std::string& source) -> void
{
    const auto vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    auto cStr = source.c_str();
    glShaderSource(vertexShaderId, 1, &cStr, nullptr);
    glCompileShader(vertexShaderId);
#ifdef _DEBUG
    verifyShader(vertexShaderId);
#endif
    glAttachShader(m_programId, vertexShaderId);
    m_attachedShaders.push_back(vertexShaderId);
}

auto ShaderProgram::attachFragmentShader(const std::string& source) -> void
{
    const auto fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    auto cStr = source.c_str();
    glShaderSource(fragmentShaderId, 1, &cStr, nullptr);
    glCompileShader(fragmentShaderId);
#ifdef _DEBUG
    verifyShader(fragmentShaderId);
#endif
    glAttachShader(m_programId, fragmentShaderId);
    m_attachedShaders.push_back(fragmentShaderId);
}

auto ShaderProgram::attachGeometryShader(const std::string& source) -> void
{
    const auto geometryShaderId = glCreateShader(GL_GEOMETRY_SHADER);
    auto cStr = source.c_str();
    glShaderSource(geometryShaderId, 1, &cStr, nullptr);
    glCompileShader(geometryShaderId);
#ifdef _DEBUG
    verifyShader(geometryShaderId);
#endif
    glAttachShader(m_programId, geometryShaderId);
    m_attachedShaders.push_back(geometryShaderId);
}

auto ShaderProgram::destroy() -> void
{
    for (auto shader : m_attachedShaders) {
        glDeleteShader(shader);
    }
    glDeleteProgram(m_programId);
}

auto ShaderProgram::setUniformMatrix(const std::string& location, const glm::mat4& matrix) const -> void
{
    this->bind();
    const auto loc = glGetUniformLocation(m_programId, location.c_str());
    if (loc == -1) {
        std::cout << "Warning: no uniform location with name " << location << std::endl;
    }
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

auto ShaderProgram::setUniformValue(const std::string & location, const glm::vec3& vector) const -> void
{
    this->bind();
    const auto loc = glGetUniformLocation(m_programId, location.c_str());
    if (loc == -1) {
        std::cout << "Warning: no uniform location with name " << location << std::endl;
    }
    glUniform3fv(loc, 1, glm::value_ptr(vector));
}

auto ShaderProgram::setUniformValue(const std::string & location, const glm::vec4 & vector) const -> void
{
    this->bind();
    const auto loc = glGetUniformLocation(m_programId, location.c_str());
    if (loc == -1) {
        std::cout << "Warning: no uniform location with name " << location << std::endl;
    }
    glUniform4fv(loc, 1, glm::value_ptr(vector));
}

auto ShaderProgram::setUniformValue(const std::string & location, const float val) const -> void
{
    this->bind();
    const auto loc = glGetUniformLocation(m_programId, location.c_str());
    if (loc == -1) {
        std::cout << "Warning: no uniform location with name " << location << std::endl;
    }
    glUniform1f(loc, val);
}

auto ShaderProgram::setUniformValue(const std::string & location, const int val) const -> void
{
    this->bind();
    const auto loc = glGetUniformLocation(m_programId, location.c_str());
    if (loc == -1) {
        std::cout << "Warning: no uniform location with name " << location << std::endl;
    }
    glUniform1i(loc, val);
}

auto ShaderProgram::setUniformValueArray(const std::string & location, const glm::vec3* arr, size_t length) -> void
{
    this->bind();
    const auto loc = glGetUniformLocation(m_programId, location.c_str());
    if (loc == -1) {
        std::cout << "Warning: no uniform location with name " << location << std::endl;
    }
    glUniform3fv(loc, length, glm::value_ptr(arr[0]));
}

auto ShaderProgram::link() -> bool
{
    glLinkProgram(m_programId);

#ifdef _DEBUG
    if (!verifyProgram(m_programId)) {
        for (auto shader : m_attachedShaders) {
            glDeleteShader(shader);
        }
        return m_valid;
    }
#endif
    for (auto shader : m_attachedShaders) {
        glDetachShader(m_programId, shader);
    }
    m_valid = true;
    return m_valid;
}

auto ShaderProgram::bind() const -> void
{
    if (m_valid) {
        glUseProgram(m_programId);
    }
}

// ReSharper disable once CppMemberFunctionMayBeStatic
auto ShaderProgram::unbind() const -> void
{
    glUseProgram(0);
}

auto ShaderProgram::getRaw() const -> GLuint
{
    return m_programId;
}

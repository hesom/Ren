#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"

#include <string>
#include <vector>

class ShaderProgram
{
private:
    GLuint m_programId;
    
    std::vector<GLuint> m_attachedShaders;

    bool m_valid;

    static bool verifyShader(GLuint shaderId);
    static bool verifyProgram(GLuint programId);
    
public:
    ShaderProgram();
    auto attachVertexShader(std::string source) -> void;
    auto attachFragmentShader(std::string source) -> void;
    auto attachGeometryShader(std::string source) -> void;

    auto destroy() -> void;

    auto setUniformMatrix(const std::string& location, const glm::mat4& matrix) -> void;
    auto setUniformValue(const std::string& location, const glm::vec3& vector) -> void;
    auto setUniformValue(const std::string& location, const glm::vec4& vector) -> void;
    auto setUniformValue(const std::string& location, float val) -> void;
    auto setUniformValue(const std::string& location, int val) -> void;
    auto setUniformValueArray(const std::string& location, const glm::vec3* arr, size_t length) -> void;

    auto link() -> bool;
    auto bind() -> void;
    auto unbind() -> void;

    auto getRaw() -> GLuint;
};
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
    auto attachVertexShader(const std::string& source) -> void;
    auto attachFragmentShader(const std::string& source) -> void;
    auto attachGeometryShader(const std::string& source) -> void;

    auto destroy() -> void;

    auto setUniformMatrix(const std::string& location, const glm::mat4& matrix) const -> void;
    auto setUniformValue(const std::string& location, const glm::vec3& vector) const -> void;
    auto setUniformValue(const std::string& location, const glm::vec4& vector) const -> void;
    auto setUniformValue(const std::string& location, float val) const -> void;
    auto setUniformValue(const std::string& location, int val) const -> void;
    auto setUniformValueArray(const std::string& location, const glm::vec3* arr, size_t length) -> void;

    auto link() -> bool;
    auto bind() const -> void;
    auto unbind() const -> void;

    auto getRaw() const -> GLuint;
};
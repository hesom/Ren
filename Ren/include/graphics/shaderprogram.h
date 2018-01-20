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

    auto link() -> bool;
    auto bind() -> void;
    auto unbind() -> void;

    auto getRaw() -> GLuint;
};
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
    void attachVertexShader(std::string source);
    void attachFragmentShader(std::string source);
    void attachGeometryShader(std::string source);

    void destroy();

    void setUniformMatrix(const std::string& location, const glm::mat4& matrix);

    bool link();
    void bind();
    void unbind();

    GLuint getRaw();
};
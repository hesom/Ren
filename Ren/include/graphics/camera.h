#pragma once

#include "glm/glm.hpp"

namespace ren
{
    class Camera
    {
    protected:
        glm::vec3 m_position;
        glm::vec3 m_viewDirection;
        glm::vec3 m_upVector;
        glm::vec3 m_rightVector;

    public:
        Camera();
        Camera(glm::vec3 position, glm::vec3 viewDirection);
        Camera(glm::vec3 position, float pitch, float yaw);

        void setPosition(glm::vec3 position);
        void setRotation(float pitch, float yaw);
        void setRotation(glm::vec3 viewDirection);

        void update();

        glm::mat4 getViewMatrix();
    };
}


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
        float m_yaw;
        float m_pitch;

    public:
        Camera();
        Camera(const glm::vec3& position, float pitch, float yaw);

        void setPosition(const glm::vec3& position);
        void setRotation(float pitch, float yaw);

        virtual void update();

        glm::mat4 getViewMatrix();
    };
}


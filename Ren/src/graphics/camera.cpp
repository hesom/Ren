#include "graphics/camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace ren
{
    Camera::Camera() :
        m_position(0.0f),
        m_viewDirection(0.0f, 0.0f, 1.0f),
        m_upVector(0.0f, 1.0f, 0.0f)
    {
        m_rightVector = glm::normalize(glm::cross(m_upVector, m_viewDirection));
        m_upVector = glm::cross(m_viewDirection, m_rightVector);
    }

    Camera::Camera(glm::vec3 position, glm::vec3 viewDirection) :
        m_position(position)
    {
        m_viewDirection = glm::normalize(viewDirection);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        m_rightVector = glm::normalize(glm::cross(up, m_viewDirection));
        m_upVector = glm::cross(m_viewDirection, m_rightVector);

    }

    Camera::Camera(glm::vec3 position, float pitch, float yaw) :
        m_position(position)
    {
        m_viewDirection = glm::normalize(position + glm::vec3(
            glm::cos(pitch)*glm::sin(yaw),
            glm::sin(pitch),
            glm::cos(pitch)*glm::cos(yaw)
        ));
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        m_rightVector = glm::normalize(glm::cross(up, m_viewDirection));
        m_upVector = glm::cross(m_viewDirection, m_rightVector);
    }

    void Camera::setPosition(glm::vec3 position)
    {
        m_position = position;
    }

    void Camera::setRotation(float pitch, float yaw)
    {
        m_viewDirection = glm::normalize(m_position + glm::vec3(
            glm::cos(pitch)*glm::sin(yaw),
            glm::sin(pitch),
            glm::cos(pitch)*glm::cos(yaw)
        ));
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        m_rightVector = glm::normalize(glm::cross(up, m_viewDirection));
        m_upVector = glm::cross(m_viewDirection, m_rightVector);
    }

    void Camera::setRotation(glm::vec3 viewDirection)
    {
        m_viewDirection = glm::normalize(viewDirection);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        m_rightVector = glm::normalize(glm::cross(up, m_viewDirection));
        m_upVector = glm::cross(m_viewDirection, m_rightVector);
    }

    glm::mat4 Camera::getViewMatrix()
    {
        return glm::lookAt(m_position, m_position + m_viewDirection, m_upVector);
    }

    void Camera::update()
    {

    }
}

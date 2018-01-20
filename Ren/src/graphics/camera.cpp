#include "graphics/camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace ren
{
    Camera::Camera() :
        m_position(0.0f),
        m_upVector(0.0f, 1.0f, 0.0f),
        m_yaw(-90.0f),
        m_pitch(0.0f)
    {
        m_viewDirection = glm::normalize(glm::vec3(
            glm::cos(glm::radians(m_pitch))*glm::sin(glm::radians(m_yaw)),
            glm::sin(glm::radians(m_pitch)),
            glm::cos(glm::radians(m_pitch))*glm::cos(glm::radians(m_yaw))
        ));
        m_rightVector = glm::normalize(glm::cross(m_upVector, m_viewDirection));
        m_upVector = glm::cross(m_viewDirection, m_rightVector);
    }

    Camera::Camera(const glm::vec3& position, float pitch, float yaw) :
        m_position(position),
        m_yaw(yaw),
        m_pitch(pitch),
        m_upVector(0.0f, 1.0f, 0.0f)
    {
        m_viewDirection = glm::normalize(glm::vec3(
            glm::cos(glm::radians(m_pitch))*glm::sin(glm::radians(m_yaw)),
            glm::sin(glm::radians(m_pitch)),
            glm::cos(glm::radians(m_pitch))*glm::cos(glm::radians(m_yaw))
        ));
    }

    auto Camera::setPosition(const glm::vec3& position) -> void
    {
        m_position = position;
    }

    auto Camera::setRotation(float pitch, float yaw) -> void
    {
        m_yaw = yaw;
        m_pitch = pitch;
        m_viewDirection = glm::normalize(glm::vec3(
            glm::cos(glm::radians(m_pitch))*glm::sin(glm::radians(m_yaw)),
            glm::sin(glm::radians(m_pitch)),
            glm::cos(glm::radians(m_pitch))*glm::cos(glm::radians(m_yaw))
        ));
    }

    auto Camera::getViewMatrix() -> glm::mat4
    {
        m_viewDirection = glm::normalize(glm::vec3(
            glm::cos(glm::radians(m_pitch))*glm::sin(glm::radians(m_yaw)),
            glm::sin(glm::radians(m_pitch)),
            glm::cos(glm::radians(m_pitch))*glm::cos(glm::radians(m_yaw))
        ));
        return glm::lookAt(m_position, m_position + m_viewDirection, m_upVector);
    }

    auto Camera::update() -> void
    {

    }
}

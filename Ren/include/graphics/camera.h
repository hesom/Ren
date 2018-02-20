#pragma once

#include "glm/glm.hpp"

namespace ren
{
    class Camera
    {
    protected:
        glm::vec3 m_position;
        glm::vec3 m_viewDirection{};
        glm::vec3 m_upVector;
        glm::vec3 m_rightVector{};
        float m_yaw;
        float m_pitch;

    public:
        virtual ~Camera() = default;
        Camera();
        Camera(const glm::vec3& position, float pitch, float yaw);

        auto setPosition(const glm::vec3& position) -> void;
        auto getPosition() const -> const decltype(m_position)&;
        auto setRotation(float pitch, float yaw) -> void;
        auto invertPitch() -> void;

        virtual auto update() -> void;

        auto getViewMatrix() -> glm::mat4;
    };
}


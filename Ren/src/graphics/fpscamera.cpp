#include "graphics/fpscamera.h"
#include "ui/inputmanager.h"
#include "util/timer.h"
#include <iostream>
namespace ren
{
    FPSCamera::FPSCamera() : Camera()
    {
        InputManager::attachKeyListener(this);
        InputManager::attachMouseListener(this);
    }

    FPSCamera::FPSCamera(glm::vec3 position, float pitch, float yaw) : Camera(position, pitch, yaw)
    {
        InputManager::attachKeyListener(this);
        InputManager::attachMouseListener(this);
    }

    FPSCamera::~FPSCamera()
    {
        InputManager::detachKeyListener(this);
        InputManager::detachMouseListener(this);
    }

    void FPSCamera::setCameraSpeed(float speed)
    {
        m_cameraSpeed = speed;
    }

    void FPSCamera::onKeyPressed(Key key, std::vector<KeyMod> mods)
    {
        switch (key) {
        case Key::KEY_W:
            m_forwardPressed = true;
            break;
        case Key::KEY_S:
            m_backwardsPressed = true;
            break;
        case Key::KEY_A:
            m_leftPressed = true;
            break;
        case Key::KEY_D:
            m_rightPressed = true;
            break;
        case Key::KEY_X:
            m_downPressed = true;
        default:
            break;
        }

        for (auto mod : mods) {
            switch (mod) {
            case KeyMod::MOD_SHIFT:
                m_upPressed = true;
            }
        }
    }

    void FPSCamera::onKeyReleased(Key key, std::vector<KeyMod> mods)
    {
        switch (key) {
        case Key::KEY_W:
            m_forwardPressed = false;
            break;
        case Key::KEY_S:
            m_backwardsPressed = false;
            break;
        case Key::KEY_A:
            m_leftPressed = false;
            break;
        case Key::KEY_D:
            m_rightPressed = false;
            break;
        case Key::KEY_X:
            m_downPressed = false;
        default:
            break;
        }

        bool shiftStillPressed = false;
        for (auto mod : mods) {
            switch (mod) {
            case KeyMod::MOD_SHIFT:
                shiftStillPressed = true;
            }
        }
        if (!shiftStillPressed) {
            m_upPressed = false;
        }
    }

    void FPSCamera::onMousePressed(MouseButton button, std::vector<KeyMod> mods)
    {
        if (button == MouseButton::MOUSE_1) {
            m_leftMouseDown = true;
        }
    }

    void FPSCamera::onMouseReleased(MouseButton button, std::vector<KeyMod> mods)
    {
        if (button == MouseButton::MOUSE_1) {
            m_leftMouseDown = false;
        }
    }

    void FPSCamera::onMouseMoved(double xpos, double ypos, double dx, double dy)
    {
        float sensitivity = 0.5f;
        m_yaw += (dx*sensitivity);
        m_pitch += (dy*sensitivity);
        if (m_pitch > 89.0f) {
            m_pitch = 89.0f;
        }
        if (m_pitch < -89.0f) {
            m_pitch = -89.0f;
        }
    }

    void FPSCamera::onMouseScroll(double xoffset, double yoffset)
    {
    }

    void FPSCamera::update()
    {
        float speed = m_cameraSpeed * Timer::deltaTime();
        if (m_forwardPressed) {
            m_position += speed * m_viewDirection;
        }
        if (m_backwardsPressed) {
            m_position -= speed * m_viewDirection;
        }
        if (m_leftPressed) {
            m_position -= glm::normalize(glm::cross(m_viewDirection, m_upVector))*speed;
        }
        if (m_rightPressed) {
            m_position += glm::normalize(glm::cross(m_viewDirection, m_upVector))*speed;
        }
        if (m_downPressed) {
            m_position -= glm::normalize(m_upVector)*speed;
        }
        if (m_upPressed) {
            m_position += glm::normalize(m_upVector)*speed;
        }
    }
}
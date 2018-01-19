#include "graphics/fpscamera.h"
#include "ui/inputmanager.h"
#include "util/timer.h"
#include <iostream>
namespace ren
{
    FPSCamera::FPSCamera() : Camera()
    {
        InputManager::attachKeyListener(this);
    }

    FPSCamera::FPSCamera(glm::vec3 position, glm::vec3 viewDirection) : Camera(position, viewDirection)
    {
        InputManager::attachKeyListener(this);
    }

    FPSCamera::FPSCamera(glm::vec3 position, float pitch, float yaw) : Camera(position, pitch, yaw)
    {
        InputManager::attachKeyListener(this);
    }

    FPSCamera::~FPSCamera()
    {
        InputManager::detachKeyListener(this);
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
        default:
            break;
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
        default:
            break;
        }
    }

    void FPSCamera::update()
    {
        float speed = m_cameraSpeed * Timer::deltaTime();
        if (m_forwardPressed) {
            std::cout << "W" << std::endl;
            m_position += speed * m_viewDirection;
        }
        if (m_backwardsPressed) {
            m_position -= speed * m_viewDirection;
        }
        if (m_leftPressed) {
            m_position -= glm::normalize(glm::cross(m_viewDirection, m_upVector))*speed;
        }
        if (m_rightPressed) {
            m_position -= glm::normalize(glm::cross(m_viewDirection, m_upVector))*speed;
        }
    }
}
#pragma once
#include "graphics/camera.h"
#include "ui/keylistener.h"
#include "ui/mouselistener.h"

namespace ren
{
    class FPSCamera : public Camera, public IKeyListener, public IMouseListener
    {
    private:
        float m_cameraSpeed = 2.5f;
        bool m_forwardPressed = false;
        bool m_leftPressed = false;
        bool m_rightPressed = false;
        bool m_backwardsPressed = false;
        bool m_leftMouseDown = false;
        bool m_downPressed = false;
        bool m_upPressed = false;

    public:
        FPSCamera();
        FPSCamera(glm::vec3 position, float pitch, float yaw);
        ~FPSCamera();
        auto setCameraSpeed(float speed) -> void;
        auto onKeyPressed(Key key, std::vector<KeyMod> mods) -> void override;
        auto onKeyReleased(Key key, std::vector<KeyMod> mods) -> void override;
        auto onMousePressed(MouseButton button, std::vector<KeyMod> mods) -> void override;
        auto onMouseReleased(MouseButton button, std::vector<KeyMod> mods) -> void override;
        auto onMouseMoved(double xpos, double ypos, double dx, double dy) -> void override;
        auto onMouseScroll(double xoffset, double yoffset) -> void override;

        auto update() -> void;
    };
}

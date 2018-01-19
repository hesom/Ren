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
        void setCameraSpeed(float speed);
        void onKeyPressed(Key key, std::vector<KeyMod> mods) override;
        void onKeyReleased(Key key, std::vector<KeyMod> mods) override;
        void onMousePressed(MouseButton button, std::vector<KeyMod> mods) override;
        void onMouseReleased(MouseButton button, std::vector<KeyMod> mods) override;
        void onMouseMoved(double xpos, double ypos, double dx, double dy) override;
        void onMouseScroll(double xoffset, double yoffset) override;

        void update();
    };
}

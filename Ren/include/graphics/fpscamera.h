#pragma once
#include "graphics/camera.h"
#include "ui/keylistener.h"


namespace ren
{
    class FPSCamera : Camera, public IKeyListener
    {
    private:
        float m_cameraSpeed = 0.1f;
        bool m_forwardPressed = false;
        bool m_leftPressed = false;
        bool m_rightPressed = false;
        bool m_backwardsPressed = false;
    public:
        FPSCamera();
        FPSCamera(glm::vec3 position, glm::vec3 viewDirection);
        FPSCamera(glm::vec3 position, float pitch, float yaw);
        ~FPSCamera();
        void setCameraSpeed(float speed);
        void onKeyPressed(Key key, std::vector<KeyMod> mods) override;
        void onKeyReleased(Key key, std::vector<KeyMod> mods) override;

        void update();
    };
}

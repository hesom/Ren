#include "util/timer.h"
#include "GLFW/glfw3.h"
namespace ren
{
    float Timer::m_deltaTime(0);
    float Timer::m_lastFrame = glfwGetTime();

    auto Timer::tick() -> void
    {
        const float currentFrame = glfwGetTime();
        m_deltaTime = currentFrame - m_lastFrame;
        m_lastFrame = currentFrame;
    }

    auto Timer::deltaTime() -> decltype(m_deltaTime)
    {
        return m_deltaTime;
    }
}
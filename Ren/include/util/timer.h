#pragma once

namespace ren
{
    class Timer
    {
    private:
        static float m_deltaTime;
        static float m_lastFrame;
        Timer() = delete;
    public:
        static auto tick() -> void;
        static auto deltaTime() -> decltype(m_deltaTime);
    };
}
#pragma once

namespace ren
{
    class Timer
    {
    private:
        static float m_deltaTime;
        static float m_lastFrame;
        Timer();
    public:
        static void tick();
        static float deltaTime();
    };
}
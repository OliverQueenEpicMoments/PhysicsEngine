#include "Time.h"

Time::Time() {
    m_PrevTime = SDL_GetPerformanceCounter();
}

void Time::Update() {
    uint64_t m_Time = SDL_GetPerformanceCounter();
    uint64_t ElapsedTime = m_Time - m_PrevTime;
    m_PrevTime = m_Time;
    m_FPS = 1 / m_DeltaTime;

    m_DeltaTime = ElapsedTime / (float)SDL_GetPerformanceFrequency();
}
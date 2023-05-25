#pragma once
#include <SDL.h>

class Time {
public:
	Time();

	void Update();
	float TimeDelta() const { return m_DeltaTime; }

	void SetFixedDeltaTime(float fixeddeltatime) { m_FixedDeltaTime = fixeddeltatime; }
	float GetFixedDeltaTime() const { return m_FixedDeltaTime; }

private:
	uint64_t m_PrevTime{ 0 };
	float m_DeltaTime{ 0 };
	float m_FixedDeltaTime{ 0 };
	float m_FPS{ 0 };
};
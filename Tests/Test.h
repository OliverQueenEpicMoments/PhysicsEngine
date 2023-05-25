#pragma once
#include "../Engine/Graphics.h"
#include "../Engine/Input.h"
#include "../Engine/Time.h"
#include "../Engine/Random.h"
#include "../Engine/World.h"
#include "../Physics/Shapes/CircleShape.h"

class Test {
public:
	Test();
	~Test();

	virtual void Initialize();
	virtual void Run();

	virtual void Update();
	virtual void FixedUpdate() = 0;

	virtual void PreRender();
	virtual void Render() = 0;
	virtual void PostRender();

	bool IsQuit() { return m_Quit; }

protected:
	void UpdateEvents();

protected:
	bool m_Quit{ false };
	float m_FixedTime{ 0 };

	Graphics* m_Graphics{ nullptr };
	Input* m_Input{ nullptr };
	Time* m_Time{ nullptr };
	World* m_World{ nullptr };
};
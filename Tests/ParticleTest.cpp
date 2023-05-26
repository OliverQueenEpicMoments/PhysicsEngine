#include "ParticleTest.h"
#include "../Physics/Body.h"

void ParticleTest::Initialize() {
	Test::Initialize();
}

void ParticleTest::Update() {
	Test::Update();

	if (m_Input->GetMouseButton(0)) {
		glm::vec2 Position = m_Graphics->ScreenToWorld(m_Input->GetMousePosition());
		glm::vec2 Velocity = RandomUnitCircle() * Randomf(5, 15);
		auto body = new Body(new CircleShape(Randomf(0.3f, 0.8f), { Randomf(), Randomf(), Randomf(), 1 }), Position, Velocity);
		body->Damping = 1;
		m_World->AddBody(body);
	}
}

void ParticleTest::FixedUpdate() {
	m_World->Step(m_Time->GetFixedDeltaTime());
}

void ParticleTest::Render() {
	m_World->Draw(m_Graphics);
	m_Graphics->DrawCircle(m_Input->GetMousePosition(), 30, { 1, 0, 0, 1 });
}
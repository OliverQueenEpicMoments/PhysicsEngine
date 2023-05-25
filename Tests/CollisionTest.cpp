#include "CollisionTest.h"
#include "../Physics/Body.h"
#include "../Physics/Shapes/CircleShape.h"

void CollisionTest::Initialize() {
	Test::Initialize();

	m_User = new Body(new CircleShape(1, { 0, 0, 1, 1 }), { 0, 0 }, { 0, 0 }, 1, Body::KINEMATIC);
	m_World->AddBody(m_User);

	auto body = new Body(new CircleShape(200, glm::vec4{ 1.0f }), { 0, -207.5 }, { 0, 0 }, 1, Body::STATIC);
	m_World->AddBody(body);
}

void CollisionTest::Update() {
	Test::Update();

	glm::vec2 Position = m_Graphics->ScreenToWorld(m_Input->GetMousePosition());
	m_User->Velocity = Position - m_User->Position;
	m_User->Position = Position;

	if (m_Input->GetMouseButton(0)) {
		glm::vec2 Velocity = { 0,0 }; // RandomUnitCircle() * Randomf(1, 3);
		float Size = Randomf(0.1f, 0.8f);

		auto body = new Body(new CircleShape(Size, { Randomf(), Randomf(), Randomf(), 1 }), Position, Velocity, Size);
		body->Damping = 0;
		body->GravityScale = 1;
		body->Restitution = 1.5f;

		m_World->AddBody(body);
	}
}

void CollisionTest::FixedUpdate() {
	m_World->Step(m_Time->GetFixedDeltaTime());
}

void CollisionTest::Render() {
	m_World->Draw(m_Graphics);
}
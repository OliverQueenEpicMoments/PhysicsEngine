#include "ForceTest.h"
#include "../Physics/Body.h"
#include "../Physics/Forces/GravitationalForce.h"
#include "../Physics/Forces/PointForce.h"
#include "../Physics/Forces/AreaForce.h"
#include "../Physics/Forces/DragForce.h"

//#define POINT_FORCE
//#define AREA_FORCE
#define DRAG_FORCE

void ForceTest::Initialize() {
	Test::Initialize();

	glm::vec2 Position = m_Graphics->ScreenToWorld({ 400, 300 });
#if defined(POINT_FORCE)
	auto body = new Body(new CircleShape(3, { 1, 1, 1, 0.2f }), Position, { 0, 0 }, 0, Body::STATIC);
	ForceGenerator* forcegenerator = new PointForce(body, 2000);
	m_World->AddForceGenerator(forcegenerator);
#elif defined(AREA_FORCE)
	auto body = new Body(new CircleShape(3, { 1, 1, 1, 0.2f }), Position, { 0, 0 }, 0, Body::STATIC);
	ForceGenerator* forceGenerator = new AreaForce(body, 2000, -90);
	m_World->AddForceGenerator(forceGenerator);
#elif defined(DRAG_FORCE)
	auto body = new Body(new CircleShape(5, { 1, 1, 1, 0.5f }), Position, { 0, 0 }, 0, Body::STATIC);
	ForceGenerator* forceGenerator = new DragForce(body, 0.75f);
	m_World->AddForceGenerator(forceGenerator);
#endif
}

void ForceTest::Update() {
	Test::Update();

	if (m_Input->GetMouseButton(0)) {
		glm::vec2 Position = m_Graphics->ScreenToWorld(m_Input->GetMousePosition());
		glm::vec2 Velocity = { 0,0 };
		//glm::vec2 Velocity = RandomUnitCircle() * Randomf(100, 250);

		float Size = Randomf(0.1f, 0.8f);
		auto body = new Body(new CircleShape(Size, { Randomf(), Randomf(), Randomf(), 1 }), Position, Velocity, Size);
		body->Damping = 1;
		body->GravityScale = 1;

		m_World->AddBody(body);
	}
}

void ForceTest::FixedUpdate() {
	m_World->Step(m_Time->GetFixedDeltaTime());
}

void ForceTest::Render() {
	m_World->Draw(m_Graphics);
	m_Graphics->DrawCircle(m_Input->GetMousePosition(), 30, { 1, 0, 0, 1 });
}
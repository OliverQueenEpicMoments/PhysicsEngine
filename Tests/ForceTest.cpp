#include "ForceTest.h"
#include "../Physics/Body.h"
#include "../Physics/Forces/GravitationalForce.h"
#include "../Physics/Forces/PointForce.h"
#include "../Physics/Forces/AreaForce.h"
#include "../Physics/Forces/DragForce.h"

#define POINT_FORCE
//#define AREA_FORCE
//#define DRAG_FORCE

void ForceTest::Initialize() {
	Test::Initialize();

#if defined(POINT_FORCE)
	auto body = new Body(new CircleShape(200, { 1, 1, 1, 0.2f }), { 400, 300 }, { 0, 0 }, 0, Body::STATIC);
	ForceGenerator* forcegenerator = new PointForce(body, 2000);
	m_World->AddForceGenerator(forcegenerator);
#elif defined(AREA_FORCE)
	auto body = new Body(new CircleShape(200, { 1, 1, 1, 0.2f }), { 400, 300 }, { 0, 0 }, 0, Body::STATIC);
	ForceGenerator* forceGenerator = new AreaForce(body, 2000, -90);
	m_World->AddForceGenerator(forceGenerator);
#elif defined(DRAG_FORCE)
	auto body = new Body(new CircleShape(200, { 1, 1, 1, 0.5f }), { 400, 300 }, { 0, 0 }, 0, Body::STATIC);
	ForceGenerator* forceGenerator = new DragForce(body, 0.5f);
	m_World->AddForceGenerator(forceGenerator);
#endif

	//auto ForceGenerator = new GravitationalForce(100);
	//m_World->AddForceGenerator(ForceGenerator);
}

void ForceTest::Update() {
	Test::Update();

	if (m_Input->GetMouseButton(0)) {
		glm::vec2 Velocity = { 0,0 };
		//glm::vec2 Velocity = RandomUnitCircle() * Randomf(100, 250);

		float Size = Randomf(1, 8);
		auto body = new Body(new CircleShape(Size * 2, { Randomf(), Randomf(), Randomf(), 1 }), m_Input->GetMousePosition(), Velocity, Size);
		body->Damping = 1;
		body->GravityScale = 20;

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
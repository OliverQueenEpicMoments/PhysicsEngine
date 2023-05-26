#include "JointTest.h"
#include "../Engine/World.h"
#include "../Physics/Body.h"
#include "../Physics/Constraints/Joint.h"
#include "../Physics/Shapes/CircleShape.h"

#define SPRING_STIFFNESS 200
#define SPRING_LENGTH 1
#define BODY_DAMPING 10
#define CHAIN_SIZE 4

void JointTest::Initialize() {
	Test::Initialize();

	m_Anchor = new Body(new CircleShape(0.5f, { 0.6f, 0, 1, 1 }), { 0, 0 }, { 0, 0 }, 0, Body::KINEMATIC);
	m_World->AddBody(m_Anchor);

	auto PrevBodyA = m_Anchor;
	auto PrevBodyB = m_Anchor;

	for (int i = 0; i < CHAIN_SIZE; i++) {
		auto BodyA = new Body(new CircleShape(0.35f, { 1, 0, 0, 1 }), { 0, 0 }, { 0, 0 }, 1, Body::DYNAMIC);
		BodyA->Damping = BODY_DAMPING;
		m_World->AddBody(BodyA);

		auto BodyB = new Body(new CircleShape(0.35f, { 0, 0, 1, 1 }), { 0, 0 }, { 0, 0 }, 1, Body::DYNAMIC);
		BodyB->Damping = BODY_DAMPING / 2;
		m_World->AddBody(BodyB);

		auto JointA = new Joint(PrevBodyA, BodyA, SPRING_STIFFNESS, SPRING_LENGTH);
		m_World->AddJoint(JointA);

		auto JointB = new Joint(PrevBodyB, BodyB, SPRING_STIFFNESS, SPRING_LENGTH);
		m_World->AddJoint(JointB);

		auto JointAPrevB = new Joint(BodyA, PrevBodyB, SPRING_STIFFNESS, SPRING_LENGTH * 2);
		m_World->AddJoint(JointAPrevB);

		auto JointBPrevA = new Joint(BodyB, PrevBodyA, SPRING_STIFFNESS, SPRING_LENGTH * 2);
		m_World->AddJoint(JointBPrevA);

		PrevBodyA = BodyA;
		PrevBodyB = BodyB;

		auto JointAB = new Joint(BodyA, BodyB, SPRING_STIFFNESS, SPRING_LENGTH * 2);
		m_World->AddJoint(JointAB);
	}
}

void JointTest::Update() {
	Test::Update();
	m_Anchor->Position = m_Graphics->ScreenToWorld(m_Input->GetMousePosition());
}

void JointTest::FixedUpdate() {
	m_World->Step(m_Time->GetFixedDeltaTime());
}

void JointTest::Render() {
	m_World->Draw(m_Graphics);
	m_Graphics->DrawCircle(m_Input->GetMousePosition(), 10, { Randomf(), Randomf(), Randomf(), 1 });
}
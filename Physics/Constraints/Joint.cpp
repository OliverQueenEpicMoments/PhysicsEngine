#include "Joint.h"
#include "../Body.h"
#include "../../Engine/Graphics.h"

Joint::Joint(Body* bodya, Body* bodyb, float stiffness, float restlength) :
	m_BodyA{ bodya },
	m_BodyB{ bodyb },
	m_Stiffness{ stiffness },
	m_RestLenght{ restlength } {
	if (m_RestLenght == 0) m_RestLenght = glm::distance(bodya->Position, bodyb->Position);
}

void Joint::Step(float dt) {
	glm::vec2 Direction = m_BodyA->Position - m_BodyB->Position;
	if (Direction == glm::vec2{ 0,0 }) return;

	float Length = glm::length(Direction);

	// F = -K * X
	float X = Length - m_RestLenght;
	//if (X < 0) return;
	float F = -m_Stiffness * X;
	glm::vec2 NDirection = glm::normalize(Direction);

	m_BodyA->ApplyForce(NDirection * F);
	m_BodyB->ApplyForce(-NDirection * F);
}

void Joint::Draw(Graphics* graphics) {
	graphics->DrawLine(graphics->WorldToScreen(m_BodyA->Position), graphics->WorldToScreen(m_BodyB->Position), glm::vec4{ 1 });
}
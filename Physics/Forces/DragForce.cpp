#include "DragForce.h"
#include "../Body.h"
#include <glm/gtx/norm.hpp>

void DragForce::Apply(std::vector<class Body*> bodies) {
	for (auto body : bodies) {
		if (!m_Body->Intersects(body)) continue;
		if (body->Velocity == glm::vec2{ 0,0 }) continue;

		float F = 0.5f * glm::length2(body->Velocity) * m_Drag;
		glm::vec2 Force = glm::normalize(body->Velocity);

		body->ApplyForce(Force * -F);
	}
}
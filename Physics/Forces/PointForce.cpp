#include "PointForce.h"
#include "../Body.h"

void PointForce::Apply(std::vector<class Body*> bodies) {
	for (auto body : bodies) {
		if (!m_Body->Intersects(body)) continue;

		glm::vec2 Direction = body->Position - m_Body->Position;
		glm::vec2 Force = glm::normalize(Direction);

		body->ApplyForce(Force * m_ForceMagnitude);
	}
}
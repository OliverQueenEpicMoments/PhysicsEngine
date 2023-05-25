#include "AreaForce.h"
#include "../Body.h"
#include <glm/gtc/quaternion.hpp>

void AreaForce::Apply(std::vector<class Body*> bodies) {
	for (auto body : bodies) {
		if (!m_Body->Intersects(body)) continue;

		glm::quat Q = glm::angleAxis(glm::radians(m_Angle), glm::vec3{ 0, 0, 1 });
		glm::vec2 Force = Q * glm::vec3{ 1, 0, 0 };

		body->ApplyForce(Force * m_ForceMagnitude);
	}
}
#include "GravitationalForce.h"
#include "../Body.h"

void GravitationalForce::Apply(std::vector<class Body*> bodies) {
	for (size_t i = 0; i < bodies.size() - 1; i++) {
		for (size_t j = i + 1; j < bodies.size(); j++) {
			Body* BodyA = bodies[i];
			Body* BodyB = bodies[j];

			glm::vec2 Direction = BodyA->Position - BodyB->Position;
			float Distance = glm::length(Direction);
			if (Distance == 0) continue;
			Distance = glm::max(1.0f, Distance);

			float Force = m_Strength * ((BodyA->Mass * BodyB->Mass) / Distance);
			glm::vec2 NDirection = glm::normalize(Direction);

			BodyA->ApplyForce(-NDirection * Force);
			BodyB->ApplyForce(NDirection * Force);
		}
	}
}
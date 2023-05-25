#pragma once
#include "../Physics/Body.h"

namespace Integrator {
	inline void ExplicitEuler(Body& body, float dt) {
		glm::vec2 Acceleration = body.Force * body.InvMass;

		body.Position += body.Velocity * dt;
		body.Velocity += Acceleration * dt;
	}

	inline void SemiImplicitEuler(Body& body, float dt) {
		glm::vec2 Acceleration = body.Force * body.InvMass;

		body.Velocity += Acceleration * dt;
		body.Position += body.Velocity * dt;
	}
}
#include "Body.h"
#include "Shapes/Shape.h"
#include "../Engine/World.h"
#include "../Engine/Integrator.h"
#include "Shapes/CircleShape.h"

bool Body::Intersects(Body* body) {
	glm::vec2 Direction = Position - body->Position;
	float Distance = glm::length(Direction);
	float Radius = dynamic_cast<CircleShape*>(shape)->Radius + dynamic_cast<CircleShape*>(body->shape)->Radius;

	return Distance <= Radius;
}

void Body::ApplyForce(const glm::vec2& force) {
	this->Force += force;
}

void Body::Step(float dt) {
	if (type != DYNAMIC) return;

	// Gravity
	ApplyForce(World::Gravity * GravityScale * Mass);

	Integrator::SemiImplicitEuler(*this, dt);
	ClearForce();

	// Damping
	Velocity *= (1.0f / (1.0f + (Damping * dt)));
}

void Body::Draw(class Graphics* graphics) {
	shape->Draw(graphics, Position);
}
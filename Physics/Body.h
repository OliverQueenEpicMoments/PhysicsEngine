#pragma once
#include <glm/glm.hpp>

class Body {
public: 
	enum Type {
		STATIC,
		KINEMATIC,
		DYNAMIC
	};

public:
	Body(class Shape* shape, const glm::vec2& position, const glm::vec2& velocity = { 0, 0 }, float mass = 1, Type type = Type::DYNAMIC) : shape{ shape }, Position{ position }, Velocity{ velocity }, Mass{ mass }, type{ type } {
		InvMass = (mass == 0 || type != DYNAMIC) ? 0 : 1 / mass;
	}

	bool Intersects(class Body* body);

	void ApplyForce(const glm::vec2& force);
	void Step(float dt);
	void Draw(class Graphics* graphics);

	void ClearForce() { Force = glm::vec2{ 0, 0 }; }

public:
	class Shape* shape{ nullptr };

	Type type{ Type::DYNAMIC };

	glm::vec2 Position{ 0, 0 };
	glm::vec2 Velocity{ 0, 0 };
	glm::vec2 Force{ 0, 0 };

	float GravityScale = 1;
	float Damping = 0;
	float Mass = 1;
	float InvMass = 1;

	float Restitution = 0.3f;
};
#pragma once
#include "glm/glm.hpp"

struct Contact {
	class Body* BodyA{ nullptr };
	class Body* BodyB{ nullptr };

	float Restitution{ 0 };
	float Depth{ 0 };
	glm::vec2 Normal{ 0, 0 };
};
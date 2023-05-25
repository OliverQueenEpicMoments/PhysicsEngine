#pragma once
#include <glm/glm.hpp>

class Shape {
public:
	Shape() {}
	Shape(const glm::vec4& color) : Color{ color } {}

	virtual void Draw(class Graphics* graphics, const glm::vec2& position) = 0;

public:
	float Size = 1;
	glm::vec4 Color{ 1, 1, 1, 1 };
};
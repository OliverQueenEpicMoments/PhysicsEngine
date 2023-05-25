#pragma once
#include "Shape.h"

class CircleShape : public Shape {
public:
	CircleShape(float radius, const glm::vec4& color) : Radius{ radius }, Shape{ color } {}

	virtual void Draw(Graphics* graphics, const glm::vec2& position) override;

public:
	float Radius = 1;
};
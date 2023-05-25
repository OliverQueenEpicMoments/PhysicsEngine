#include "CircleShape.h"
#include "../../Engine/Graphics.h"

void CircleShape::Draw(Graphics* graphics, const glm::vec2& position) {
	int R = graphics->WorldToPixels(Radius);
	graphics->DrawFilledCircle(graphics->WorldToScreen(position), R, Color);
}
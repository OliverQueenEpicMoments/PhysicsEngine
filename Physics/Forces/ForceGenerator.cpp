#include "ForceGenerator.h"
#include "../Body.h"

void ForceGenerator::Draw(Graphics* graphics) {
	if (m_Body) m_Body->Draw(graphics);
}
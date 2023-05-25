#pragma once
#include "ForceGenerator.h"

class DragForce : public ForceGenerator {
public:
	DragForce(class Body* body, float drag) : ForceGenerator{ body }, m_Drag{ drag } {}

	virtual void Apply(std::vector<class Body*> bodies) override;

protected:
	float m_Drag{ 0 };
};
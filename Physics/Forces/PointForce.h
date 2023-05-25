#pragma once
#include "ForceGenerator.h"

class PointForce : public ForceGenerator {
public:
	PointForce(class Body* body, float forcemagnitude) : ForceGenerator{ body }, m_ForceMagnitude{ forcemagnitude } {}

	virtual void Apply(std::vector<class Body*> bodies) override;

protected:
	float m_ForceMagnitude{ 1 };
};
#pragma once
#include "ForceGenerator.h"

class AreaForce : public ForceGenerator {
public:
	AreaForce(class Body* body, float forcemagnitude, float angle) : ForceGenerator{ body }, m_ForceMagnitude{ forcemagnitude }, m_Angle{ angle } {}

	virtual void Apply(std::vector<class Body*> bodies) override;

protected:
	float m_ForceMagnitude{ 1 };
	float m_Angle{ 0 };
};
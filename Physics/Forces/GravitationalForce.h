#pragma once
#include "ForceGenerator.h"

class GravitationalForce : public ForceGenerator {
public:
	GravitationalForce(float strength) : m_Strength{ strength } {}
	void Apply(std::vector<class Body*> bodies) override;

private:
	float m_Strength = 0;
};
#include "World.h"
#include "../Physics/Body.h"
#include "../Physics/Constraints/Joint.h"
#include "../Physics/Forces/ForceGenerator.h"
#include "../Physics/Collision/Collision.h"
#include <vector>

glm::vec2 World::Gravity{ 0, -9.8f };

World::~World() {
	for (auto Body : m_Bodies) delete Body;
	m_Bodies.clear();
}

void World::Step(float dt) {
	std::vector<Body*> Bodies(m_Bodies.begin(), m_Bodies.end());
	if (!m_Bodies.empty() && !m_ForceGenerators.empty()) {
		for (auto ForceGenerator : m_ForceGenerators) ForceGenerator->Apply(Bodies);
	}

	for (auto Body : Bodies) Body->Step(dt);
	for (auto Joint : m_Joints) Joint->Step(dt);

	// Collisions
	std::vector<Contact> contacts;
	Collision::CreateContacts(Bodies, contacts);
	Collision::SeparateContacts(contacts);
	Collision::ResolveContacts(contacts);
}

void World::Draw(Graphics* graphics) {
	for (auto Joint : m_Joints) Joint->Draw(graphics);
	for (auto ForceGenerator : m_ForceGenerators) ForceGenerator->Draw(graphics);
	for (auto Body : m_Bodies) Body->Draw(graphics);
}

void World::AddBody(Body* body) {
	m_Bodies.push_back(body);
}

void World::RemoveBody(Body* body) {
	m_Bodies.remove(body);
}

void World::AddJoint(Joint* joint) {
	m_Joints.push_back(joint);
}

void World::RemoveJoint(Joint* joint) {
	m_Joints.remove(joint);
}

void World::AddForceGenerator(ForceGenerator* forcegenerator) {
	m_ForceGenerators.push_back(forcegenerator);
}
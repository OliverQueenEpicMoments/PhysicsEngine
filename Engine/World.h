#pragma once
#include <list>
#include <vector>
#include "../Physics/Body.h"

class World {
public: 
	~World();

	void Step(float dt);
	void Draw(class Graphics* graphics);

	void AddBody(Body* body);
	void RemoveBody(Body* body);

	void AddJoint(class Joint* joint);
	void RemoveJoint(class Joint* joint);

	void AddForceGenerator(class ForceGenerator* forcegenerator);

public:
	static glm::vec2 Gravity;

private:
	std::list<Body*> m_Bodies;
	std::list<class Joint*> m_Joints;
	std::vector<class ForceGenerator*> m_ForceGenerators;
};
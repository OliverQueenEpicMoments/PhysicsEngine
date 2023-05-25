#pragma once

class Body;

class Joint {
public:
	Joint(Body* bodya, Body* bodyb, float stiffness, float restlength = 0);
	
	void Step(float dt);
	void Draw(class Graphics* graphics);

protected:
	float m_RestLenght{ 0 };
	float m_Stiffness{ 0 };

	Body* m_BodyA{ nullptr };
	Body* m_BodyB{ nullptr };
};
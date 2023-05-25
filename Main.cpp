#include "Tests/ParticleTest.h"
#include "Tests/ForceTest.h"
#include "Tests/JointTest.h"
#include "Tests/CollisionTest.h"

int main(int argc, char* argv[]) {
	Test* Testing = new CollisionTest();
	Testing->Initialize();
	while (!Testing->IsQuit()) Testing->Run();
	delete Testing;

	return 0;
}
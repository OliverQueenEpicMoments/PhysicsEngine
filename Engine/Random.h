#pragma once
#include <random>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

inline void SeedRandom(int seed) { srand(seed); }

inline int Random() { return rand(); }
inline int Random(int max) { return Random() % max; } // exclusive (0 <-> (max - 1))
inline int Random(int min, int max) { return min + Random(max - min) + 1; } // inclusive (min <-> max)

inline float Randomf() { return (float)rand() / RAND_MAX; } // 0.0 <-> 1.0
inline float Randomf(float max) { return Randomf() * max; } // 0.0 <-> max
inline float Randomf(float min, float max) { return min + Randomf(max - min); } // min <-> max

inline glm::vec2 RandomUnitCircle() {
	glm::quat Q = glm::angleAxis(Randomf(glm::two_pi<float>()), glm::vec3{ 0, 0, 1 });
	return Q * glm::vec3{ 1, 0, 0 };
}
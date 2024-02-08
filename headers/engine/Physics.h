#ifndef PHYSICS_H
#define PHYSICS_H

#include "Entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Physics {
public:
	Physics() = delete;

	// returns the overlap of two entities
	static glm::vec3 GetOverlap(std::shared_ptr<Entity>&, std::shared_ptr<Entity>&);
	// returns the overlap of two entities using the previous positions
	static glm::vec3 GetPreviousOverlap(std::shared_ptr<Entity>&, std::shared_ptr<Entity>&);
	// returns the terminal velocity of an entity
	static float GetTerminalVelocity(std::shared_ptr<Entity>&);
	// returns true if a ray intersects an entity, takes ray origin, ray end, and an entity as 
	// parameters
	static bool RayIntersect(glm::vec3, glm::vec3, std::shared_ptr<Entity>&);
};

#endif
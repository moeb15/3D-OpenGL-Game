#ifndef RAY_CASTER_H
#define RAY_CASTER_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class RayCast {
public:
	RayCast() = delete;

	// returns origin of ray and direction of ray given mouse position, projection matrix, and view matrix
	static std::vector<glm::vec3> ScreenPosToWorldRay(glm::vec2, glm::mat4, glm::mat4);
	// returns whether a point lies along a ray given the point, ray origin, ray end point, and 3 error bounds for 
	// the x, y , and z direction
	static bool RayIntersect(glm::vec3, glm::vec3, glm::vec3);

};

#endif // !RAY_CASTER_H


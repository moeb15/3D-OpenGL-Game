#include "RayCaster.h"


std::vector<glm::vec3> RayCast::ScreenPosToWorldRay(glm::vec2 mousePos, glm::mat4 proj, glm::mat4 view) {
	glm::mat4 invProjView = glm::inverse(proj * view);
	std::vector<glm::vec3> data;

	glm::vec4 rayStartNDC = glm::vec4(mousePos, -1.0, 1.0);
	glm::vec4 rayEndNDC = glm::vec4(mousePos, 0.0, 1.0);

	glm::vec4 rayStartWorld = invProjView * rayStartNDC;
	rayStartWorld /= rayStartWorld.w;
	glm::vec4 rayEndWorld = invProjView * rayEndNDC;
	rayEndWorld /= rayEndWorld.w;

	glm::vec3 rayDir = glm::vec3(rayEndWorld - rayStartWorld);
	rayDir = glm::normalize(rayDir);

	data.push_back(rayStartWorld);
	data.push_back(rayDir);

	return data;
}

bool RayCast::RayContainsPoint(glm::vec3 point, glm::vec3 rayStart, glm::vec3 rayEnd, float errX,
	float errY, float errZ) {
	glm::vec3 rayStartToPoint = point - rayStart;
	glm::vec3 ray = rayEnd - rayStart;
	if (rayStartToPoint.length <= ray.length) {
		rayStartToPoint = glm::normalize(rayStartToPoint);
		ray = glm::normalize(ray);
		
		float dx = fabsf(ray.x - rayStartToPoint.x);
		float dy = fabsf(ray.y - rayStartToPoint.y);
		float dz = fabsf(ray.z - rayStartToPoint.z);

		return (dx <= errX) && (dy <= errY) && (dz <= errZ);
	}
	return false;
}
#include "RayCaster.h"
#include <iostream>

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

bool RayCast::RayIntersect(glm::vec3 point, glm::vec3 rayStart, glm::vec3 rayEnd) {
	glm::vec3 ray = rayEnd;
//	ray = glm::normalize(ray);
	glm::vec3 rayStartToPoint = point - rayStart;
//	rayStartToPoint = glm::normalize(rayStartToPoint);

	float rayLenSq = glm::dot(ray, ray);
	float rayDotPoint = glm::dot(rayStartToPoint, ray);
	float t = rayDotPoint / rayLenSq;

	return (t >= 0) && (t <= 1);
}
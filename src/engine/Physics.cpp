#include "Physics.h"


glm::vec3 Physics::GetOverlap(std::shared_ptr<Entity>& e1, std::shared_ptr<Entity>& e2) {
	if (e1->hasComponent<CBoundingBox>() && e2->hasComponent<CBoundingBox>() &&
		e1->hasComponent<CTransform>() && e2->hasComponent<CTransform>()) {
		glm::vec3& e1Size = e1->getComponent<CBoundingBox>().size;
		glm::vec3& e2Size = e2->getComponent<CBoundingBox>().size;
		
		glm::vec3& e1Pos = e1->getComponent<CTransform>().pos;
		glm::vec3& e2Pos = e2->getComponent<CTransform>().pos;

		float dx = fabsf(e1Pos.x - e1Pos.x);
		float dy = fabsf(e1Pos.y - e1Pos.y);
		float dz = fabsf(e1Pos.z - e1Pos.z);

		return glm::vec3(
			(e1Size.x + e2Size.x) / 2.f - dx,
			(e1Size.y + e2Size.y) / 2.f - dy,
			(e1Size.z + e2Size.z) / 2.f - dz
		);
	}

	return glm::vec3(0.0);
}

glm::vec3 Physics::GetPreviousOverlap(std::shared_ptr<Entity>& e1, std::shared_ptr<Entity>& e2) {
	if (e1->hasComponent<CBoundingBox>() && e2->hasComponent<CBoundingBox>() &&
		e1->hasComponent<CTransform>() && e2->hasComponent<CTransform>()) {
		glm::vec3& e1Size = e1->getComponent<CBoundingBox>().size;
		glm::vec3& e2Size = e2->getComponent<CBoundingBox>().size;

		glm::vec3& e1Pos = e1->getComponent<CTransform>().prevPos;
		glm::vec3& e2Pos = e2->getComponent<CTransform>().prevPos;

		float dx = fabsf(e1Pos.x - e1Pos.x);
		float dy = fabsf(e1Pos.y - e1Pos.y);
		float dz = fabsf(e1Pos.z - e1Pos.z);

		return glm::vec3(
			(e1Size.x + e2Size.x) / 2.f - dx,
			(e1Size.y + e2Size.y) / 2.f - dy,
			(e1Size.z + e2Size.z) / 2.f - dz
		);
	}

	return glm::vec3(0.0);
}
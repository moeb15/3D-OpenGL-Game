#include "Physics.h"


glm::vec3 Physics::GetOverlap(std::shared_ptr<Entity>& e1, std::shared_ptr<Entity>& e2) {
	if (e1->hasComponent<CBoundingBox>() && e1->hasComponent<CTransform>() &&
		e2->hasComponent<CBoundingBox>() && e2->hasComponent<CTransform>()) {
		glm::vec3& e1Size = e1->getComponent<CBoundingBox>().size;
		glm::vec3& e2Size = e2->getComponent<CBoundingBox>().size;
		
		glm::vec3& e1Pos = e1->getComponent<CTransform>().pos;
		glm::vec3& e2Pos = e2->getComponent<CTransform>().pos;

		float dx = fabsf(e1Pos.x - e2Pos.x + e1Size.x / 2.f - e2Size.x / 2.f);
		float dy = fabsf(e1Pos.y - e2Pos.y + e1Size.y / 2.f - e2Size.y / 2.f);
		float dz = fabsf(e1Pos.z - e2Pos.z + e1Size.z / 2.f - e2Size.z / 2.f);

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

		float dx = fabsf(e1Pos.x - e2Pos.x + e1Size.x / 2.f - e2Size.x / 2.f);
		float dy = fabsf(e1Pos.y - e2Pos.y + e1Size.y / 2.f - e2Size.y / 2.f);
		float dz = fabsf(e1Pos.z - e2Pos.z + e1Size.z / 2.f - e2Size.z / 2.f);

		return glm::vec3(
			(e1Size.x + e2Size.x) / 2.f - dx,
			(e1Size.y + e2Size.y) / 2.f - dy,
			(e1Size.z + e2Size.z) / 2.f - dz
		);
	}

	return glm::vec3(0.0);
}

float Physics::GetTerminalVelocity(std::shared_ptr<Entity>& e) {
	if (e->hasComponent<CTransform>() &&
		e->hasComponent<CMass>() &&
		e->hasComponent<CGravity>() &&
		e->hasComponent<CBoundingBox>()) {
		auto& transform = e->getComponent<CTransform>();
		float dragCoef = 1.81f;
		float airDensity = 1.293f;

		float size = e->getComponent<CBoundingBox>().size.length();

		float numerator = 2 * e->getComponent<CMass>().mass 
				* e->getComponent<CGravity>().gravity.y;
		float denominator = size * airDensity * dragCoef;

		return numerator / denominator;
	}
	return 0.0f;
}

bool Physics::RayIntersect(glm::vec3 rayStart, glm::vec3 rayDir, std::shared_ptr<Entity>& e) {
	if (e->hasComponent<CTransform>() &&
		e->hasComponent<CBoundingBox>()) {
		auto& transform = e->getComponent<CTransform>();
		auto& bbox = e->getComponent<CBoundingBox>();
			
		float tMin = 0.0f;
		float tMax = 100000.0f;

		glm::mat4 model = glm::mat4(1.0);
		model = glm::scale(model, transform.scale);
		model = glm::translate(model, transform.pos);
		
		glm::vec3 aabbMax = bbox.size;
		glm::vec3 aabbMin = aabbMax * -1.f;

		glm::vec3 xAxis = glm::vec3(model[0].x, model[0].y, model[0].z);
		glm::vec3 yAxis = glm::vec3(model[1].x, model[1].y, model[1].z);
		glm::vec3 zAxis = glm::vec3(model[2].x, model[2].y, model[2].z);

		glm::vec3 entityWorldPos = glm::vec3(model[3].x, model[3].y, model[3].z);

		glm::vec3 delta = entityWorldPos - rayStart;

		// intersection with planes perpendical to xAxis
		{
			float e = glm::dot(xAxis, delta);
			float f = glm::dot(rayDir, xAxis);
			if (fabsf(f) > 0.001f) {
				// calculate distances between rayStart and ray plane interesctions
				float t1 = (e + aabbMin.x) / f; // "left" plane intersection
				float t2 = (e + aabbMax.x) / f; // "right" plane intersection

				// t1 represents nearest, swap if needed
				if (t1 > t2) {
					float w = t1;
					t1 = t2;
					t2 = w;
				}

				// tMax is the nearest "far" intersection (amongst the X,Y and Z planes pairs)
				if (t2 < tMax) {
					tMax = t2;
				}
				// tMin is the farthest "near" intersection (amongst the X,Y and Z planes pairs)
				if (t1 > tMin) {
					tMin = t1;
				}

				// if the nearest "far" intersection is closer than the 
				// furthest "near" intersection, there is no intersection
				if (tMax < tMin) {
					return false;
				}
			}
			else { // ray is parallel to the planes
				if (-e + aabbMin.x > 0.0f || -e + aabbMax.x < 0.0f) {
					return false;
				}
			}
		}

		// intersection with planes perpendical to yAxis
		{
			float e = glm::dot(yAxis, delta);
			float f = glm::dot(rayDir, yAxis);
			if (fabsf(f) > 0.001f) {
				float t1 = (e + aabbMin.y) / f; 
				float t2 = (e + aabbMax.y) / f; 

				if (t1 > t2) {
					float w = t1;
					t1 = t2;
					t2 = w;
				}

				if (t2 < tMax) {
					tMax = t2;
				}
				if (t1 > tMin) {
					tMin = t1;
				}
				if (tMax < tMin) {
					return false;
				}
			}
			else { 
				if (-e + aabbMin.y > 0.0f || -e + aabbMax.y < 0.0f) {
					return false;
				}
			}
		}

		// intersection with planes perpendical to zAxis
		{
			float e = glm::dot(zAxis, delta);
			float f = glm::dot(rayDir, zAxis);
			if (fabsf(f) > 0.001f) {
				float t1 = (e + aabbMin.z) / f;
				float t2 = (e + aabbMax.z) / f; 

				if (t1 > t2) {
					float w = t1;
					t1 = t2;
					t2 = w;
				}

				if (t2 < tMax) {
					tMax = t2;
				}
				if (t1 > tMin) {
					tMin = t1;
				}
				if (tMax < tMin) {
					return false;
				}
			}
			else { 
				if (-e + aabbMin.z > 0.0f || -e + aabbMax.z < 0.0f) {
					return false;
				}
			}
		}

		std::cout << tMin << std::endl;
		return true;
	}
	return false;
}
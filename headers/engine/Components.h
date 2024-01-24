#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CTransform {
public:
	glm::vec3 pos;
	glm::vec3 scale;
	bool has = false;

	CTransform(){}
};

class CInput {
	bool forward = false;
	bool backward = false;
	bool left = false;
	bool right = false;
	bool has = false;

	CInput(){}
};
#endif

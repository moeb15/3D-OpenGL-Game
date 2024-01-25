#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "Shader.h"
#include "ShaderTags.h"
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class CTransform {
public:
	glm::vec3 pos = glm::vec3(0.0f);
	glm::vec3 prevPos = glm::vec3(0.0f);
	glm::vec3 vel = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);
	bool has = false;

	//CTransform(){}
};

class CBoundingBox {
public:
	glm::vec3 size = glm::vec3(1.0);
	bool has = false;
};

class CHandle {
public:
	//std::unordered_map<ShaderTags::ID, unsigned int> handles;
	unsigned int VAO;
	unsigned int VBO;
	bool has = false;
};

class CShader {
public:
	Shader shader;
	bool has = false;

	CShader(){}
	CShader(const Shader& sh):
		shader(sh){}
};

class CColor {
public:
	glm::vec3 color = glm::vec3(0.0f);
	bool has = false;

	//CColor(){}
};

class CInput {
public:
	bool forward = false;
	bool backward = false;
	bool left = false;
	bool right = false;
	bool has = false;

	//CInput(){}
};
#endif

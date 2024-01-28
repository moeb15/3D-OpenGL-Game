#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "Shader.h"
#include "Model.h"
#include "ShaderTags.h"
#include "EntityTags.h"
#include "Texture.h"
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
	float pitch = 0;
	float yaw = 90.f;
	bool has = false;

	//CTransform(){}
};

class CModel {
public:
	Model model;

	CModel(){}
	CModel(const char* path) :
		model(Model(path)) {}
};

class CBoundingBox {
public:
	glm::vec3 size = glm::vec3(1.0);
	bool collide = false;
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

class CTexture {
public:
	Texture diffuseMap;
	Texture specularMap;
	Texture emissionMap;
	bool has = false;
};

class CInput {
public:
	bool forward = false;
	bool backward = false;
	bool left = false;
	bool right = false;
	bool jump = false;
	bool has = false;

	//CInput(){}
};

class CGravity {
public:
	glm::vec3 gravity = glm::vec3(0, 25, 0);
	bool has = false;
};

class CState {
public:
	EntityState::ID state = EntityState::None;
	bool has = false;
};

#endif

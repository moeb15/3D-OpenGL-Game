#include "DefaultScene.h"
#include "glad.h"
#include "ResourceManager.h"
#include "GameEngine.h"
#include "ShaderTags.h"
#include "VBO.h"
#include "Physics.h"

DefaultScene::DefaultScene(GameEngine* engine):
	Scene(engine){

	init();
}

void DefaultScene::init() {
	registerCommand(GLFW_KEY_LEFT, CommandTags::Left);
	registerCommand(GLFW_KEY_RIGHT, CommandTags::Right);
	registerCommand(GLFW_KEY_UP, CommandTags::Up);
	registerCommand(GLFW_KEY_DOWN, CommandTags::Down);

	spawnLightSource();
	spawnPlayer();
	spawnBoxes(4);
}

void DefaultScene::spawnLightSource() {
	float vertices[] = {
		// positions // normals // texture coords
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};

	m_LightSource = m_EM.addEntity(Entities::LightSoruce);
	m_LightSource->addComponent<CTransform>();
	m_LightSource->getComponent<CTransform>().pos = glm::vec3(1.0, 4.0, 10);
	m_LightSource->getComponent<CTransform>().scale = glm::vec3(0.2);

	m_LightSource->addComponent<CShader>(ResourceManager::LoadShader("assets/shaders/lightingShader.vert",
		"assets/shaders/lightingShader.frag"));

	m_LightSource->addComponent<CColor>();
	m_LightSource->getComponent<CColor>().color = glm::vec3(1.0, 1.0, 1.0);

	m_LightSource->addComponent<CHandle>();
	unsigned int& boxVBO = m_LightSource->getComponent<CHandle>().VBO;
	unsigned int& boxVAO = m_LightSource->getComponent<CHandle>().VAO;

	glGenVertexArrays(1, &boxVAO);
	glBindVertexArray(boxVAO);

	VBO::BuildVBO(GL_ARRAY_BUFFER, boxVBO, vertices, sizeof(vertices),
		GL_STATIC_DRAW);
	VBO::BindVBO(GL_ARRAY_BUFFER, boxVBO);

	for (int i = 0; i < 2; i++) {
		VBO::EnableVBO(i, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
			(void*)(i * 3 * sizeof(float)));
	}

	VBO::UnBindVBO(GL_ARRAY_BUFFER);
	glBindVertexArray(0);
}

void DefaultScene::spawnPlayer() {
	float vertices[] = {
		// positions // normals // texture coords
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};

	m_Player = m_EM.addEntity(Entities::Player);
	m_Player->addComponent<CTransform>();
	m_Player->getComponent<CTransform>().pos = glm::vec3(0, 0, -3);
		
	m_Player->addComponent<CBoundingBox>();

	m_Player->addComponent<CInput>();

	m_Player->addComponent<CShader>(ResourceManager::LoadShader("assets/shaders/vertShader.vert",
		"assets/shaders/fragShader.frag"));

	m_Player->addComponent<CColor>();
	m_Player->getComponent<CColor>().color = glm::vec3(1.0, 0, 0);

	m_Player->addComponent<CHandle>();
	unsigned int& boxVBO = m_Player->getComponent<CHandle>().VBO;
	unsigned int& boxVAO = m_Player->getComponent<CHandle>().VAO;

	glGenVertexArrays(1, &boxVAO);
	glBindVertexArray(boxVAO);

	VBO::BuildVBO(GL_ARRAY_BUFFER, boxVBO, vertices, sizeof(vertices),
		GL_STATIC_DRAW);
	VBO::BindVBO(GL_ARRAY_BUFFER, boxVBO);

	for (int i = 0; i < 2; i++) {
		VBO::EnableVBO(i, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
			(void*)(i * 3 * sizeof(float)));
	}

	VBO::UnBindVBO(GL_ARRAY_BUFFER);
	glBindVertexArray(0);
}

void DefaultScene::spawnBoxes(unsigned int boxCount) {
	float vertices[] = {
		// positions // normals // texture coords
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};
	glm::vec3 boxPos[] = {
		glm::vec3(0,2,-3),
		glm::vec3(0,-2,-3),
		glm::vec3(2,0,-3),
		glm::vec3(-2,0,-3),
	};

	for (int i = 0; i < boxCount; i++) {
		auto& box = m_EM.addEntity(Entities::Box);
		box->addComponent<CTransform>();
		box->getComponent<CTransform>().pos = boxPos[i % 4];

		box->addComponent<CBoundingBox>();

		box->addComponent<CShader>(ResourceManager::LoadShader("assets/shaders/vertShader.vert",
			"assets/shaders/fragShader.frag"));

		box->addComponent<CColor>();
		box->getComponent<CColor>().color = glm::vec3(0, 0, 1.0);

		box->addComponent<CHandle>();
		unsigned int& boxVBO = box->getComponent<CHandle>().VBO;
		unsigned int& boxVAO = box->getComponent<CHandle>().VAO;

		glGenVertexArrays(1, &boxVAO);
		glBindVertexArray(boxVAO);

		VBO::BuildVBO(GL_ARRAY_BUFFER, boxVBO, vertices, sizeof(vertices),
			GL_STATIC_DRAW);
		VBO::BindVBO(GL_ARRAY_BUFFER, boxVBO);

		for (int i = 0; i < 2; i++) {
			VBO::EnableVBO(i, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
				(void*)(i * 3 * sizeof(float)));
		}

		VBO::UnBindVBO(GL_ARRAY_BUFFER);
		glBindVertexArray(0);
	}
}

void DefaultScene::update(float dt) {
	m_EM.update();

	sMovement(dt);
	sCollision();
	sRender();
}

void DefaultScene::sMovement(float dt) {
	auto& input = m_Player->getComponent<CInput>();
	auto& transform = m_Player->getComponent<CTransform>();
	glm::vec3 playerVel = glm::vec3(0.0f);

	if (input.left == true) {
		playerVel.x = -5;
	}
	if (input.right == true) {
		playerVel.x = 5;
	}
	if (input.forward == true) {
		playerVel.y = 5;
	}
	if (input.backward == true) {
		playerVel.y = -5;
	}
	
	transform.vel = playerVel;

	for (auto& e : m_EM.getEntities()) {
		e->getComponent<CTransform>().prevPos =
			e->getComponent<CTransform>().pos;

		e->getComponent<CTransform>().pos +=
			e->getComponent<CTransform>().vel * dt;
	}
}

void DefaultScene::sDoCommand(const Command& cmd){
	if (cmd.getType() == CommandTags::Start) {
		if (cmd.getName() == CommandTags::Left) {
			m_Player->getComponent<CInput>().left = true;
		}
		if (cmd.getName() == CommandTags::Right) {
			m_Player->getComponent<CInput>().right = true;
		}
		if (cmd.getName() == CommandTags::Up) {
			m_Player->getComponent<CInput>().forward = true;
		}
		if (cmd.getName() == CommandTags::Down) {
			m_Player->getComponent<CInput>().backward = true;
		}
	}
	else if(cmd.getType() == CommandTags::Stop) {
		if (cmd.getName() == CommandTags::Left) {
			m_Player->getComponent<CInput>().left = false;
		}
		if (cmd.getName() == CommandTags::Right) {
			m_Player->getComponent<CInput>().right = false;
		}
		if (cmd.getName() == CommandTags::Up) {
			m_Player->getComponent<CInput>().forward = false;
		}
		if (cmd.getName() == CommandTags::Down) {
			m_Player->getComponent<CInput>().backward = false;
		}
	}
}

void DefaultScene::sCollision() {
	for (auto& e : m_EM.getEntities()) {
		if (e->tag() == Entities::Player) {
			continue;
		}
		glm::vec3 overlap = Physics::GetOverlap(m_Player, e);
		if (overlap.x > 0 && overlap.y > 0 && overlap.z > 0) {
			std::cout << "Collision Detected!" << std::endl;
		}
	}
}

void DefaultScene::sRender() {
	glm::mat4 model = glm::mat4(1.0);
	glm::mat4 view = m_Engine->getCamera().GetViewMatrix();
	glm::mat4 proj = glm::perspective(glm::radians(m_Engine->getCamera().Zoom),
		1280.f / 720.f, 0.1f, 100.f);

	for (auto& e : m_EM.getEntities()) {
		if (e->tag() != Entities::LightSoruce) {
			if (e->hasComponent<CTransform>() &&
				e->hasComponent<CShader>() &&
				e->hasComponent<CColor>() &&
				e->hasComponent<CHandle>() &&
				e->hasComponent<CBoundingBox>()) {
				model = glm::scale(model, e->getComponent<CTransform>().scale);
				model = glm::translate(model, e->getComponent<CTransform>().pos);
				e->getComponent<CShader>().shader.use();
				e->getComponent<CShader>().shader.setMat4("model", model);
				e->getComponent<CShader>().shader.setMat4("view", view);
				e->getComponent<CShader>().shader.setMat4("projection", proj);

				e->getComponent<CShader>().shader.setVec3("material.ambient",
					e->getComponent<CColor>().color);
				e->getComponent<CShader>().shader.setVec3("material.diffuse",
					e->getComponent<CColor>().color);
				e->getComponent<CShader>().shader.setVec3("material.specular",
					glm::vec3(1.0, 1.0, 0.0));
				e->getComponent<CShader>().shader.setFloat("material.shininess",
					32.f);

				e->getComponent<CShader>().shader.setVec3("light.ambient",
					glm::vec3(0.2));
				e->getComponent<CShader>().shader.setVec3("light.diffuse",
					glm::vec3(0.5));
				e->getComponent<CShader>().shader.setVec3("light.specular",
					glm::vec3(1.0));

				e->getComponent<CShader>().shader.setVec3("lightPos",
					m_LightSource->getComponent<CTransform>().pos);

				glBindVertexArray(e->getComponent<CHandle>().VAO);
				glDrawArrays(GL_TRIANGLES, 0, 36);

				model = glm::mat4(1.0);
			}
		}
		else {
			model = glm::scale(model, e->getComponent<CTransform>().scale);
			model = glm::translate(model, e->getComponent<CTransform>().pos);
			e->getComponent<CShader>().shader.use();
			e->getComponent<CShader>().shader.setMat4("model", model);
			e->getComponent<CShader>().shader.setMat4("view", view);
			e->getComponent<CShader>().shader.setMat4("projection", proj);

			e->getComponent<CShader>().shader.setVec3("lightColor",
				e->getComponent<CColor>().color);

			glBindVertexArray(e->getComponent<CHandle>().VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			model = glm::mat4(1.0);
		}
	}
}
#include "DefaultScene.h"
#include "glad.h"
#include "ResourceManager.h"
#include "GameEngine.h"
#include "ShaderTags.h"
#include "VBO.h"

DefaultScene::DefaultScene(GameEngine* engine):
	Scene(engine){

	init();
}

void DefaultScene::init() {
	registerCommand(GLFW_KEY_LEFT, CommandTags::Left);
	registerCommand(GLFW_KEY_RIGHT, CommandTags::Right);
	registerCommand(GLFW_KEY_UP, CommandTags::Forward);
	registerCommand(GLFW_KEY_DOWN, CommandTags::Backward);

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
	/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);*/
	
	VBO::UnBindVBO(GL_ARRAY_BUFFER);
	glBindVertexArray(0);
}

void DefaultScene::update(float dt) {
	m_EM.update();

	sMovement(dt);
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
		playerVel.z = -5;
	}
	if (input.backward == true) {
		playerVel.z = 5;
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

void DefaultScene::sRender() {
	glm::mat4 model = glm::mat4(1.0);
	glm::mat4 view = m_Engine->getCamera().GetViewMatrix();
	glm::mat4 proj = glm::perspective(glm::radians(m_Engine->getCamera().Zoom),
		1280.f / 720.f, 0.1f, 100.f);

	for (auto& e : m_EM.getEntities()) {
		if (e->tag() == Entities::Player) {
			model = glm::scale(model, e->getComponent<CTransform>().scale);
			model = glm::translate(model, e->getComponent<CTransform>().pos);
			e->getComponent<CShader>().shader.use();
			e->getComponent<CShader>().shader.setMat4("model", model);
			e->getComponent<CShader>().shader.setMat4("view", view);
			e->getComponent<CShader>().shader.setMat4("projection", proj);
			e->getComponent<CShader>().shader.setVec3("objColor",
				e->getComponent<CColor>().color);
			e->getComponent<CShader>().shader.setVec3("lightColor",
				glm::vec3(1.0, 1.0, 1.0));
			e->getComponent<CShader>().shader.setVec3("lightPos",
				glm::vec3(3.2, 5.0, 3.0));

			glBindVertexArray(e->getComponent<CHandle>().VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
}
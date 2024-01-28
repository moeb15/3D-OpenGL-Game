#include "DefaultScene.h"
#include "glad.h"
#include "ResourceManager.h"
#include "GameEngine.h"
#include "ShaderTags.h"
#include "VBO.h"
#include "Physics.h"
#include "Utils.h"

DefaultScene::DefaultScene(GameEngine* engine):
	Scene(engine),
	m_DirectionalLight(-0.5,-0.5,-0.5){

	init();
}

void DefaultScene::init() {
	registerCommand(GLFW_KEY_A, CommandTags::Left);
	registerCommand(GLFW_KEY_D, CommandTags::Right);
	registerCommand(GLFW_KEY_W, CommandTags::Forward);
	registerCommand(GLFW_KEY_S, CommandTags::Backward);
	registerCommand(GLFW_KEY_SPACE, CommandTags::Jump);
	registerCommand(GLFW_KEY_T, CommandTags::ToggleCamera);
	registerCommand(GLFW_KEY_ESCAPE, CommandTags::Quit);

	spawnLightSource();
	spawnPlayer();
	buildScene();
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
	m_LightSource->getComponent<CTransform>().pos = glm::vec3(0,10, 0);
	m_LightSource->getComponent<CTransform>().scale = glm::vec3(0.2);

	m_LightSource->addComponent<CShader>(ResourceManager::LoadShader("assets/shaders/lightingShader.vert",
		"assets/shaders/lightingShader.frag"));

	m_LightSource->addComponent<CColor>();
	m_LightSource->getComponent<CColor>().color = glm::vec3(1.0);

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
	m_Player->getComponent<CTransform>().pos = glm::vec3(0, 1.0, 3);
		
	m_Player->addComponent<CBoundingBox>();
	m_Player->addComponent<CInput>();
	m_Player->addComponent<CGravity>();
	m_Player->addComponent<CState>();

	m_Player->addComponent<CShader>(ResourceManager::LoadShader("assets/shaders/vertShader.vert",
		"assets/shaders/fragShader.frag"));
	
	m_Player->addComponent<CTexture>();
	m_Player->getComponent<CTexture>().diffuseMap = ResourceManager::LoadTexture("assets/graphics/container2.png");
	m_Player->getComponent<CTexture>().specularMap = ResourceManager::LoadTexture("assets/graphics/container2_specular.png");

	m_Player->addComponent<CHandle>();
	unsigned int& boxVBO = m_Player->getComponent<CHandle>().VBO;
	unsigned int& boxVAO = m_Player->getComponent<CHandle>().VAO;

	glGenVertexArrays(1, &boxVAO);
	glBindVertexArray(boxVAO);

	VBO::BuildVBO(GL_ARRAY_BUFFER, boxVBO, vertices, sizeof(vertices),
		GL_STATIC_DRAW);
	VBO::BindVBO(GL_ARRAY_BUFFER, boxVBO);

	for (int i = 0; i < 3; i++) {
		if (i == 2) {
			VBO::EnableVBO(i, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
				(void*)(i * 3 * sizeof(float)));
			break;
		}
		VBO::EnableVBO(i, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
			(void*)(i * 3 * sizeof(float)));
	}

	VBO::UnBindVBO(GL_ARRAY_BUFFER);
	glBindVertexArray(0);
}

void DefaultScene::buildScene() {
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

	std::vector<std::vector<int>> positionData = Utils::getSceneVector("assets/scenes/defaultscene.txt");

	for (int i = 0; i < positionData.size(); i++) {
		auto& box = m_EM.addEntity(Entities::Box);
		box->addComponent<CTransform>();
		box->getComponent<CTransform>().pos = glm::vec3(
			positionData[i][0],
			positionData[i][1],
			positionData[i][2]
		);

		box->addComponent<CBoundingBox>();

		box->addComponent<CShader>(ResourceManager::LoadShader("assets/shaders/vertShader.vert",
			"assets/shaders/fragShader.frag"));

		box->addComponent<CTexture>();
		box->getComponent<CTexture>().diffuseMap = ResourceManager::LoadTexture("assets/graphics/container.jpg");

		box->addComponent<CHandle>();
		unsigned int& boxVBO = box->getComponent<CHandle>().VBO;
		unsigned int& boxVAO = box->getComponent<CHandle>().VAO;

		glGenVertexArrays(1, &boxVAO);
		glBindVertexArray(boxVAO);

		VBO::BuildVBO(GL_ARRAY_BUFFER, boxVBO, vertices, sizeof(vertices),
			GL_STATIC_DRAW);
		VBO::BindVBO(GL_ARRAY_BUFFER, boxVBO);

		for (int i = 0; i < 3; i++) {
			if (i == 2) {
				VBO::EnableVBO(i, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
					(void*)(i * 3 * sizeof(float)));
				break;
			}
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

	if (!m_Engine->IsCameraFree()) {
		if (input.left == true) {
			playerVel.z = -5 * sin(-glm::radians(transform.yaw - 90.f));
			playerVel.x = -5 * cos(glm::radians(transform.yaw - 90.f));
		}
		if (input.right == true) {
			playerVel.z = 5 * sin(-glm::radians(transform.yaw - 90.f));
			playerVel.x = 5 * cos(glm::radians(transform.yaw - 90.f));
		}
		if (input.forward == true) {
			playerVel.z = -5 * cos(glm::radians(transform.yaw - 90.f));
			playerVel.x = -5 * sin(glm::radians(transform.yaw - 90.f));
		}
		if (input.backward == true) {
			playerVel.z = 5 * cos(glm::radians(transform.yaw - 90.f));
			playerVel.x = 5 * sin(glm::radians(transform.yaw - 90.f));
		}
		if (input.jump == true &&
			transform.vel.y == 0) {
			playerVel.y = 6;
		}
		else {
			playerVel.y = transform.vel.y;
		}
	}
	
	transform.vel = playerVel;

	for (auto& e : m_EM.getEntities()) {
		e->getComponent<CTransform>().prevPos =
			e->getComponent<CTransform>().pos;
		if (e->hasComponent<CGravity>() && 
			e->hasComponent<CState>()) {
			if (e->getComponent<CState>().state == EntityState::Air) {
				e->getComponent<CTransform>().vel -=
					e->getComponent<CGravity>().gravity * 0.5f * dt;
			}
			else {
				e->getComponent<CTransform>().vel.y = 0;
			}
		}

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
		if (cmd.getName() == CommandTags::Forward) {
			m_Player->getComponent<CInput>().forward = true;
		}
		if (cmd.getName() == CommandTags::Backward) {
			m_Player->getComponent<CInput>().backward = true;
		}
		if (cmd.getName() == CommandTags::Jump) {
			m_Player->getComponent<CInput>().jump = true;
			m_Player->getComponent<CState>().state = EntityState::Air;
		}
		if (cmd.getName() == CommandTags::ToggleCamera) {
			m_Engine->toggleCamera();
		}
		if (cmd.getName() == CommandTags::Quit) {
			glfwSetWindowShouldClose(m_Engine->getWindow(), 1);
		}
	}
	else if(cmd.getType() == CommandTags::Stop) {
		if (cmd.getName() == CommandTags::Left) {
			m_Player->getComponent<CInput>().left = false;
		}
		if (cmd.getName() == CommandTags::Right) {
			m_Player->getComponent<CInput>().right = false;
		}
		if (cmd.getName() == CommandTags::Forward) {
			m_Player->getComponent<CInput>().forward = false;
		}
		if (cmd.getName() == CommandTags::Backward) {
			m_Player->getComponent<CInput>().backward = false;
		}
		if (cmd.getName() == CommandTags::Jump) {
			m_Player->getComponent<CInput>().jump = false;
		}
	}
}

void DefaultScene::sCollision() {
	for (auto& e : m_EM.getEntities(Entities::Box)) {
		glm::vec3 overlap = Physics::GetOverlap(m_Player, e);
		if (overlap.x > 0 && overlap.y > 0 && overlap.z > 0) {
			m_Player->getComponent<CTransform>().pos.y += overlap.y;
			m_Player->getComponent<CBoundingBox>().collide = true;
			m_Player->getComponent<CState>().state = EntityState::Ground;
			break;
		}
		else {
			m_Player->getComponent<CBoundingBox>().collide = false;
		}
	}
	if (!m_Player->getComponent<CBoundingBox>().collide) {
		m_Player->getComponent<CState>().state = EntityState::Air;
	}
}

void DefaultScene::sRender() {
	glm::mat4 model = glm::mat4(1.0);
	glm::mat4 view = m_Engine->getCamera().GetViewMatrix();
	glm::mat4 proj = glm::perspective(glm::radians(m_Engine->getCamera().Zoom),
		1280.f / 720.f, 0.1f, 100.f);

	/*m_LightSource->getComponent<CColor>().color = glm::vec3(
		fabsf(sin((float)glfwGetTime())),
		fabsf(cos((float)glfwGetTime())),
		fabsf(sin(cos((float)glfwGetTime())))
	);*/

	if (!m_Engine->IsCameraFree()) {
		m_Engine->getCamera().Position = 
			m_Player->getComponent<CTransform>().pos + glm::vec3(0,1.0,0);
		m_Player->getComponent<CTransform>().yaw =
			-m_Engine->getCamera().Yaw;
	}

	for (auto& e : m_EM.getEntities()) {
		if (e->tag() != Entities::LightSoruce) {
			model = glm::scale(model, e->getComponent<CTransform>().scale);
			model = glm::translate(model, e->getComponent<CTransform>().pos);
			model = glm::rotate(model, glm::radians(
				e->getComponent<CTransform>().yaw),
				glm::vec3(0.0, 1.0, 0.0));

			e->getComponent<CShader>().shader.use();
			e->getComponent<CShader>().shader.setMat4("model", model);
			e->getComponent<CShader>().shader.setMat4("view", view);
			e->getComponent<CShader>().shader.setMat4("projection", proj);

			if (e->tag() == Entities::Player) {
				e->getComponent<CTexture>().diffuseMap.activate(GL_TEXTURE0);
				e->getComponent<CTexture>().specularMap.activate(GL_TEXTURE1);

				e->getComponent<CShader>().shader.setInt("material.diffuseMap", 0);
				e->getComponent<CShader>().shader.setInt("material.specularMap", 1);
				e->getComponent<CShader>().shader.setInt("material.emissionMap", 2);
			}
			else {
				e->getComponent<CTexture>().diffuseMap.activate(GL_TEXTURE0);
				e->getComponent<CShader>().shader.setInt("material.diffuseMap", 0);
				e->getComponent<CShader>().shader.setInt("material.specularMap", 1);
				e->getComponent<CShader>().shader.setInt("material.emissionMap", 2);
			}

			e->getComponent<CShader>().shader.setFloat("material.shininess",
				32.f);

			e->getComponent<CShader>().shader.setVec3("pointLight.ambient",
				m_LightSource->getComponent<CColor>().color);
			e->getComponent<CShader>().shader.setVec3("pointLight.diffuse",
				m_LightSource->getComponent<CColor>().color * glm::vec3(0.5));
			e->getComponent<CShader>().shader.setVec3("pointLight.specular",
				m_LightSource->getComponent<CColor>().color);

			e->getComponent<CShader>().shader.setVec3("pointLight.position",
				m_LightSource->getComponent<CTransform>().pos);
			e->getComponent<CShader>().shader.setFloat("pointLight.constant", 1.0f);
			e->getComponent<CShader>().shader.setFloat("pointLight.linear", 0.045f);
			e->getComponent<CShader>().shader.setFloat("pointLight.quadratic", 0.0075f);

			e->getComponent<CShader>().shader.setVec3("dirLight.direction",
				m_DirectionalLight);
			e->getComponent<CShader>().shader.setVec3("dirLight.ambient",
				m_LightSource->getComponent<CColor>().color * glm::vec3(0.2));
			e->getComponent<CShader>().shader.setVec3("dirLight.diffuse",
				m_LightSource->getComponent<CColor>().color * glm::vec3(0.1));
			e->getComponent<CShader>().shader.setVec3("dirLight.specular",
				m_LightSource->getComponent<CColor>().color);

			e->getComponent<CShader>().shader.setVec3("lightPos",
				m_LightSource->getComponent<CTransform>().pos);

			glBindVertexArray(e->getComponent<CHandle>().VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			model = glm::mat4(1.0);
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
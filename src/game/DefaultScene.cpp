#include "DefaultScene.h"
#include "glad.h"
#include "ResourceManager.h"
#include "GameEngine.h"
#include "ShaderTags.h"
#include "VBO.h"
#include "Physics.h"
#include "Utils.h"
#include "RayCaster.h"

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

DefaultScene::DefaultScene(GameEngine* engine):
	Scene(engine),
	m_DirectionalLight(-0.5,-0.5,-0.5){

	init();
}

EntityManager::EntityVec& DefaultScene::getSceneEntities() {
	return m_EM.getEntities();
}

void DefaultScene::init() {
	registerCommand(GLFW_KEY_A, CommandTags::Left);
	registerCommand(GLFW_KEY_D, CommandTags::Right);
	registerCommand(GLFW_KEY_W, CommandTags::Forward);
	registerCommand(GLFW_KEY_S, CommandTags::Backward);
	registerCommand(GLFW_KEY_SPACE, CommandTags::Jump);
	registerCommand(GLFW_KEY_T, CommandTags::ToggleCamera);
	registerCommand(GLFW_KEY_ESCAPE, CommandTags::Quit);
	registerCommand(GLFW_MOUSE_BUTTON_1, CommandTags::LeftMouseClick);
	registerCommand(GLFW_MOUSE_BUTTON_2, CommandTags::RightMouseClick);

	m_Paused = true;


	loadResources();
//	spawnLightSource();
//	spawnBox(glm::vec3(0, 10, 0));
	spawnPlayer();
	//spawnModel();
	buildScene();
}

void DefaultScene::addToScene(Entities::ID tag, glm::vec3 pos) {
	switch (tag) {
	case Entities::Box:
		spawnBox(pos);
		break;

	case Entities::TestModel:
		spawnModel(pos);
		break;
	
	case Entities::LightSoruce:
		spawnLightSource(pos);
		break;
	}
}

void DefaultScene::loadResources() {
	// Adding shaders
	m_Engine->getResources().AddShader(ResourceTags::Shaders::DefaultShader,
		"assets/shaders/vertShader.vert", "assets/shaders/fragShader.frag");

	m_Engine->getResources().AddShader(ResourceTags::Shaders::LightingShader,
		"assets/shaders/lightingShader.vert", "assets/shaders/lightingShader.frag");

	m_Engine->getResources().AddShader(ResourceTags::ModelShader,
		"assets/shaders/modelShaders.vert", "assets/shaders/modelShaders.frag");

	m_Engine->getResources().AddShader(ResourceTags::BulletShader,
		"assets/shaders/bulletShader.vert", "assets/shaders/bulletShader.frag");

	// Adding textures
	m_Engine->getResources().AddTexture(ResourceTags::Textures::PlayerDiffuse, "assets/graphics/container2.png");
	m_Engine->getResources().AddTexture(ResourceTags::Textures::PlayerSpecular, "assets/graphics/container2_specular.png");

	m_Engine->getResources().AddTexture(ResourceTags::Textures::ContainerDiffuse, "assets/graphics/container.jpg");
	m_Engine->getResources().AddTexture(ResourceTags::Textures::ContainerEmission, "assets/graphics/matrix.jpg");

	// Adding models
	m_Engine->getResources().AddModel(ResourceTags::Models::DefaultModel, "assets/graphics/models/backpack/backpack.obj");
}

void DefaultScene::spawnLightSource(const glm::vec3& pos) {
	m_LightSourceCount++;
	std::shared_ptr<Entity> lightSourceEntity = m_EM.addEntity(Entities::LightSoruce);
	lightSourceEntity->addComponent<CTransform>();
	lightSourceEntity->getComponent<CTransform>().pos = pos;
	//lightSourceEntity->getComponent<CTransform>().scale = glm::vec3(0.2);

	lightSourceEntity->addComponent<CBoundingBox>();
	lightSourceEntity->getComponent<CBoundingBox>().size *=
		lightSourceEntity->getComponent<CTransform>().scale;
	lightSourceEntity->addComponent<CDraggable>();

	lightSourceEntity->addComponent<CShader>(m_Engine->getResources().LoadShader(ResourceTags::Shaders::LightingShader));

	lightSourceEntity->addComponent<CColor>();
	lightSourceEntity->getComponent<CColor>().color = m_LightColor;

	lightSourceEntity->addComponent<CHandle>();
	unsigned int& boxVBO = lightSourceEntity->getComponent<CHandle>().VBO;
	unsigned int& boxVAO = lightSourceEntity->getComponent<CHandle>().VAO;

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

void DefaultScene::spawnModel(glm::vec3& pos) {
	std::shared_ptr<Entity> modelEntity = m_EM.addEntity(Entities::TestModel);
	modelEntity->addComponent<CTransform>();
	modelEntity->getComponent<CTransform>().pos = pos;
	modelEntity->getComponent<CTransform>().scale = glm::vec3(1.0);
	modelEntity->addComponent<CBoundingBox>();
	modelEntity->getComponent<CBoundingBox>().size = glm::vec3(2, 3, 1);
	modelEntity->addComponent<CDraggable>();
	
	modelEntity->addComponent<CShader>(m_Engine->getResources().LoadShader(ResourceTags::Shaders::ModelShader));
	modelEntity->addComponent<CModel>(m_Engine->getResources().LoadModel(ResourceTags::Models::DefaultModel));
}

void DefaultScene::spawnPlayer() {

	m_Player = m_EM.addEntity(Entities::Player);
	m_Player->addComponent<CTransform>();
	m_Player->getComponent<CTransform>().pos = glm::vec3(0, 1.0, 3);
		
	m_Player->addComponent<CBoundingBox>();
	m_Player->addComponent<CInput>();
	m_Player->addComponent<CGravity>();
	m_Player->addComponent<CState>();
	m_Player->addComponent<CMass>();
	m_Player->getComponent<CMass>().mass = 10;

	m_Player->addComponent<CShader>(m_Engine->getResources().LoadShader(ResourceTags::Shaders::DefaultShader));
	
	m_Player->addComponent<CTexture>();
	m_Player->getComponent<CTexture>().diffuseMap = m_Engine->getResources().LoadTexture(ResourceTags::Textures::PlayerDiffuse);
	m_Player->getComponent<CTexture>().specularMap = m_Engine->getResources().LoadTexture(ResourceTags::Textures::PlayerSpecular);

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

void DefaultScene::spawnBullet(std::shared_ptr<Entity>& originEntity) {
	auto& originTransform = originEntity->getComponent<CTransform>();

	std::shared_ptr<Entity> bullet = m_EM.addEntity(Entities::Bullet);
	bullet->addComponent<CTransform>();
	// not spawning for origin entity position, needs to be fixed
	bullet->getComponent<CTransform>().pos = originTransform.pos + glm::vec3(0.0,20.0,0.0); 
	bullet->getComponent<CTransform>().scale = glm::vec3(0.1);
	bullet->getComponent<CTransform>().yaw = originTransform.yaw;
	bullet->getComponent<CTransform>().vel.z = -1000 * cos(glm::radians(originTransform.yaw - 90.f));
	bullet->getComponent<CTransform>().vel.x = -1000 * sin(glm::radians(originTransform.yaw - 90.f));
	bullet->getComponent<CTransform>().vel.y = 1000*sin(glm::radians(originTransform.pitch));

	bullet->addComponent<CState>();
	bullet->getComponent<CState>().state = EntityState::Air;
	bullet->addComponent<CColor>();
	bullet->getComponent<CColor>().color = glm::vec3(0.0);
	bullet->addComponent<CGravity>();
	bullet->addComponent<CLifespan>();
	bullet->getComponent<CLifespan>().lifespan = 5.f;

	bullet->addComponent<CShader>(m_Engine->getResources().LoadShader(ResourceTags::Shaders::BulletShader));

	bullet->addComponent<CHandle>();
	unsigned int& bulletVBO = bullet->getComponent<CHandle>().VBO;
	unsigned int& bulletVAO = bullet->getComponent<CHandle>().VAO;

	glGenVertexArrays(1, &bulletVAO);
	glBindVertexArray(bulletVAO);

	VBO::BuildVBO(GL_ARRAY_BUFFER, bulletVBO, vertices, sizeof(vertices),
		GL_STATIC_DRAW);
	VBO::BindVBO(GL_ARRAY_BUFFER, bulletVBO);

	for (int i = 0; i < 2; i++) {
		VBO::EnableVBO(i, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
			(void*)(i * 3 * sizeof(float)));
	}

	VBO::UnBindVBO(GL_ARRAY_BUFFER);
	glBindVertexArray(0);
}

void DefaultScene::spawnBox(const glm::vec3& pos) {
	std::shared_ptr<Entity> box = m_EM.addEntity(Entities::Box);
	box->addComponent<CTransform>();
	box->getComponent<CTransform>().pos = pos;

	box->addComponent<CBoundingBox>();
	box->addComponent<CDraggable>();
	Shader defaultShader = m_Engine->getResources().LoadShader(ResourceTags::Shaders::DefaultShader);
	box->addComponent<CShader>(defaultShader);

	box->addComponent<CTexture>();
	box->getComponent<CTexture>().diffuseMap = m_Engine->getResources().LoadTexture(ResourceTags::Textures::ContainerDiffuse);
	box->getComponent<CTexture>().emissionMap = m_Engine->getResources().LoadTexture(ResourceTags::Textures::ContainerEmission);

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

void DefaultScene::buildScene() {

	std::unordered_map<Entities::ID, 
		std::vector<std::vector<int>>> positionData = Utils::getSceneVector("assets/scenes/defaultscene.txt");
	glm::vec3 pos;

	for (auto& kvPair : positionData) {
		switch (kvPair.first) {
		case Entities::Box:
			for (int i = 0; i < kvPair.second.size(); i++) {
				pos.x = kvPair.second[i][0];
				pos.y = kvPair.second[i][1];
				pos.z = kvPair.second[i][2];

				spawnBox(pos);
			}
			break;

		case Entities::LightSoruce:
			for (int i = 0; i < kvPair.second.size(); i++) {
				pos.x = kvPair.second[i][0];
				pos.y = kvPair.second[i][1];
				pos.z = kvPair.second[i][2];

				spawnLightSource(pos);
			}
			break;
		}
	}
}

void DefaultScene::update(float dt) {
	m_EM.update();

	if (!m_Paused) {
		sLifespan(dt);
		sMovement(dt);
	}
	sDraggable();
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
				if (e->getComponent<CTransform>().vel.y * e->getComponent<CTransform>().vel.y >
					Physics::GetTerminalVelocity(e) && Physics::GetTerminalVelocity(e) > 0.0f) {
					e->getComponent<CTransform>().vel.y = -sqrt(Physics::GetTerminalVelocity(e));
				}
				else {
					e->getComponent<CTransform>().vel -=
						e->getComponent<CGravity>().gravity * 0.5f * dt;
				}
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
			m_Paused = !m_Paused;
		}
		if (cmd.getName() == CommandTags::Quit) {
			glfwSetWindowShouldClose(m_Engine->getWindow(), 1);
		}
		if (!m_Engine->IsCameraFree()) {
			if (cmd.getName() == CommandTags::LeftMouseClick) {
				spawnBullet(m_Player);
			}
		}
		else if(!m_Engine->IsEditorToggled()){
			if (cmd.getName() == CommandTags::LeftMouseClick) {
				glm::mat4 view = m_Engine->getCamera().GetViewMatrix();
				glm::mat4 proj = glm::perspective(glm::radians(m_Engine->getCamera().Zoom),
					1280.f / 720.f, 0.1f, 100.f);

				auto rayData = RayCast::ScreenPosToWorldRay(glm::vec2(0.0f), proj, view);
				float minDist = std::numeric_limits<float>::max();
				float prevDist = minDist;
				int curID = -1;

				for (auto& e : m_EM.getEntities()) {
					if (Physics::RayIntersect(rayData[0], rayData[1], e, minDist)) {
						if (minDist < prevDist) {
							curID = e->id();
						}
						prevDist = minDist;
					}
				}
				if (curID != -1) {
					//std::cout << "Entity " << curID << " Clicked!" << std::endl;
					for(auto& e : m_EM.getEntities()){
						if (e->id() != curID) {
							continue;
						}
						else {
							if (e->hasComponent<CDraggable>()) {
								e->getComponent<CDraggable>().draggable =
									!e->getComponent<CDraggable>().draggable;
							}
						}
					}
				}
			}
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

void DefaultScene::sLifespan(float dt) {
	for (auto& e : m_EM.getEntities()) {
		if (e->hasComponent<CLifespan>()) {
			if (e->getComponent<CLifespan>().lifespan <= 0.0f) {
				e->destroy();
			}
			else {
				e->getComponent<CLifespan>().lifespan -= dt;
			}
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

void DefaultScene::sDraggable(){
	for (auto& e : m_EM.getEntities()) {
		if (e->hasComponent<CDraggable>()) {
			if (e->getComponent<CDraggable>().draggable) {
				e->getComponent<CTransform>().pos =
					m_Engine->getCamera().Position
					+ m_Engine->getCamera().Front * 5.f;
			}
		}
	}
}

void DefaultScene::sRender() {
	glm::mat4 model = glm::mat4(1.0);
	glm::mat4 view = m_Engine->getCamera().GetViewMatrix();
	glm::mat4 proj = glm::perspective(glm::radians(m_Engine->getCamera().Zoom),
		1280.f / 720.f, 0.1f, 100.f);

	auto& lightSources = m_EM.getEntities(Entities::LightSoruce);
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
		m_Player->getComponent<CTransform>().pitch =
			m_Engine->getCamera().Pitch;
	}

	for (auto& e : m_EM.getEntities()) {
		if (e->tag() == Entities::Box ||
			e->tag() == Entities::Player) {
			model = glm::scale(model, e->getComponent<CTransform>().scale);
			model = glm::translate(model, e->getComponent<CTransform>().pos);
			model = glm::rotate(model, glm::radians(
				e->getComponent<CTransform>().yaw),
				glm::vec3(0.0, 1.0, 0.0));
			model = glm::rotate(model, glm::radians(
				e->getComponent<CTransform>().pitch),
				glm::vec3(0.0, 0.0, 1.0));

			e->getComponent<CShader>().shader.use();
			e->getComponent<CShader>().shader.setMat4("model", model);
			e->getComponent<CShader>().shader.setMat4("view", view);
			e->getComponent<CShader>().shader.setMat4("projection", proj);
			e->getComponent<CShader>().shader.setInt("lightCount", m_LightSourceCount);

			if (e->tag() == Entities::Player) {
				e->getComponent<CTexture>().diffuseMap.activate(GL_TEXTURE1);
				e->getComponent<CTexture>().specularMap.activate(GL_TEXTURE2);

				e->getComponent<CShader>().shader.setInt("material.diffuseMap", 1);
				e->getComponent<CShader>().shader.setInt("material.specularMap", 2);
				e->getComponent<CShader>().shader.setInt("material.emissionMap", 4);
			}
			else {
				e->getComponent<CTexture>().diffuseMap.activate(GL_TEXTURE1);
				e->getComponent<CTexture>().specularMap.activate(GL_TEXTURE2);
				if (e->hasComponent<CDraggable>()) {
					if (e->getComponent<CDraggable>().draggable) {
						e->getComponent<CTexture>().emissionMap.activate(GL_TEXTURE3);
						e->getComponent<CShader>().shader.setInt("material.emissionMap", 3);
					}
					else {
						e->getComponent<CShader>().shader.setInt("material.emissionMap", 4);
					}
				}
				e->getComponent<CShader>().shader.setInt("material.diffuseMap", 1);
				e->getComponent<CShader>().shader.setInt("material.specularMap", 2);
			}

			e->getComponent<CShader>().shader.setFloat("material.shininess",
				32.f);

			for (int i = 0; i < m_LightSourceCount; i++) {
				e->getComponent<CShader>().shader.setVec3(
					"pointLights[" + std::to_string(i) + "].ambient",
					m_LightColor);
				e->getComponent<CShader>().shader.setVec3(
					"pointLights[" + std::to_string(i) + "].diffuse",
					m_LightColor * glm::vec3(0.5));
				e->getComponent<CShader>().shader.setVec3(
					"pointLights[" + std::to_string(i) + "].specular",
					m_LightColor);

				e->getComponent<CShader>().shader.setVec3(
					"pointLights[" + std::to_string(i) + "].position",
					lightSources[i]->getComponent<CTransform>().pos);
				e->getComponent<CShader>().shader.setFloat(
					"pointLights[" + std::to_string(i) + "].constant", 1.0f);
				e->getComponent<CShader>().shader.setFloat(
					"pointLights[" + std::to_string(i) + "].linear", 0.045f);
				e->getComponent<CShader>().shader.setFloat(
					"pointLights[" + std::to_string(i) + "].quadratic", 0.0032f);
			}

			e->getComponent<CShader>().shader.setVec3("dirLight.direction",
				m_DirectionalLight);
			e->getComponent<CShader>().shader.setVec3("dirLight.ambient",
				m_LightColor * glm::vec3(0.1));
			e->getComponent<CShader>().shader.setVec3("dirLight.diffuse",
				m_LightColor * glm::vec3(0.1));
			e->getComponent<CShader>().shader.setVec3("dirLight.specular",
				m_LightColor * glm::vec3(1.0));
			
			e->getComponent<CShader>().shader.setVec3("lightPos",
				m_Engine->getCamera().Position);

			glBindVertexArray(e->getComponent<CHandle>().VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			model = glm::mat4(1.0);
		}
		else if(e->tag() == Entities::LightSoruce){
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
		else if(e->tag() == Entities::TestModel){
			model = glm::translate(model, e->getComponent<CTransform>().pos);
			model = glm::scale(model, e->getComponent<CTransform>().scale);
			e->getComponent<CShader>().shader.use();
			e->getComponent<CShader>().shader.setMat4("model", model);
			e->getComponent<CShader>().shader.setMat4("view", view);
			e->getComponent<CShader>().shader.setMat4("projection", proj);
			e->getComponent<CModel>().model.Draw(
				e->getComponent<CShader>().shader
			);
			model = glm::mat4(1.0);
		}
		else if (e->tag() == Entities::Bullet) {
			model = glm::scale(model, e->getComponent<CTransform>().scale);
			model = glm::translate(model, e->getComponent<CTransform>().pos);
			model = glm::rotate(model, glm::radians(
				e->getComponent<CTransform>().yaw),
				glm::vec3(0.0, 1.0, 0.0));

			e->getComponent<CShader>().shader.use();
			e->getComponent<CShader>().shader.setMat4("model",model);
			e->getComponent<CShader>().shader.setMat4("view",view);
			e->getComponent<CShader>().shader.setMat4("projection",proj);
			e->getComponent<CShader>().shader.setVec3("bulletColor",
				e->getComponent<CColor>().color);

			glBindVertexArray(e->getComponent<CHandle>().VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			model = glm::mat4(1.0);
		}
	}
}
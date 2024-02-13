#include "GameEngine.h"
#include "glad.h"
#include "Shader.h"
#include "DefaultScene.h"
#include <stdexcept>
#include <cassert>

GameEngine* GameEngine::engine = nullptr;

GameEngine::GameEngine() {
	assert(engine == nullptr);
	
	m_ToggleCamera = true;
	m_ToggleEditor = true;
	m_MouseX = 1280 / 2.f;
	m_MouseY = 720 / 2.f;
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Start = true;

	m_Window = glfwCreateWindow(1280, 720, "Game Engine", NULL, NULL);
	if (m_Window == NULL) {
		glfwTerminate();
		throw std::runtime_error("GameEngine failed to create OpenGL window");
	}
	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("GameEngine failed to create OpenGL window");
	}

	std::shared_ptr<DefaultScene> dScene(
		new DefaultScene(this));

	m_CurrentScene = Scenes::Default;
	m_SceneMap.insert(std::make_pair(Scenes::Default,
		std::static_pointer_cast<Scene>(dScene)));

	engine = this;
}


void GameEngine::run() {
	initPairs();
	glm::vec3 entityPos;
	std::string sceneName;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsClassic();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	glViewport(0, 0, 1280, 720);
	glfwSetFramebufferSizeCallback(m_Window, resize_callback);
	glfwSetMouseButtonCallback(m_Window, mouse_click_callback);
	glfwSetCursorPosCallback(m_Window, mouse_callback);
	glfwSetKeyCallback(m_Window, key_callback);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(m_Window)) {
		glfwPollEvents();
		
		if (IsCameraFree() && !io.WantCaptureKeyboard) {
			freeCamera(m_Window, m_DT);
		}

		m_CurTime = (float)glfwGetTime();
		engine->m_DT = m_CurTime - m_LastTime;
		m_LastTime = m_CurTime;

		glClearColor(0.52, 0.8, 0.9, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		update(m_DT);

		if (m_ToggleEditor) {
			sceneEditor(entityPos, sceneName);
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(m_Window);
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}

void GameEngine::initPairs() {
	for (int i = 0; i < Entities::EntityCount; i++) {
		m_EntityPairs[static_cast<Entities::ID>(i)] = false;
	}
}

void GameEngine::sceneEditor(glm::vec3& entityPos, std::string& scene) {
	int w, h;
	glfwGetWindowSize(m_Window, &w, &h);

	ImGui::SetWindowSize(ImVec2(w / 5, h/4));
	ImGui::SetWindowPos(ImVec2(0, 0));

	ImGui::SetNextWindowSizeConstraints(ImVec2(w / 6, h * 2 / 3.f), ImVec2(w / 6, h * 2 / 3.f));

	ImGui::Begin("Scene Editor Window");

	ImGui::Text("Position");
	ImGui::SliderFloat("X", &entityPos.x, -20.f, 20.f);
	ImGui::SliderFloat("Y", &entityPos.y, -20.f, 20.f);
	ImGui::SliderFloat("Z", &entityPos.z, -20.f, 20.f);

	ImGui::Text("Entity Type");
	for (auto& kvPair : m_EntityPairs) {
		switch (kvPair.first) {
		case Entities::Box:
			ImGui::Checkbox("Box", &kvPair.second);
			break;

		case Entities::LightSoruce:
			ImGui::Checkbox("LightSource", &kvPair.second);
			break;

		case Entities::TestModel:
			ImGui::Checkbox("TestModel", &kvPair.second);

		default:
			break;
		}
	}
	if (ImGui::Button("Add")) {
		for (auto& kvPair : m_EntityPairs) {
			if (kvPair.second) {
				getCurrentScene()->addToScene(kvPair.first, entityPos);
			}
		}
	}

	ImGui::Text("Scene Name");
	ImGui::InputText("Name", &scene);
	if (ImGui::Button("Save")) {
		std::ofstream sceneFile("assets/scenes/" + std::string(scene) + ".txt");
		EntityManager::EntityVec& entities = m_SceneMap[m_CurrentScene]->getSceneEntities();
		std::string line;
		for (auto& e : entities) {
			if (e->hasComponent<CTransform>()) {
				glm::vec3& pos = e->getComponent<CTransform>().pos;
				
				switch (e->tag()) {
				case Entities::Box:
					line = "Box " + std::to_string((int)pos.x) + " "
						+ std::to_string((int)pos.y) + " "
						+ std::to_string((int)pos.z) + "\n";
					sceneFile << line;
					break;

				case Entities::LightSoruce:
					line = "Light " + std::to_string((int)pos.x) + " "
						+ std::to_string((int)pos.y) + " "
						+ std::to_string((int)pos.z) + "\n";
					sceneFile << line;
					break;
				}
			}
		}
		sceneFile.close();
	}

	ImGui::End();

	ImGui::SetNextWindowSizeConstraints(ImVec2(w / 6, h / 3), ImVec2(w / 6, h / 3));
	ImGui::SetNextWindowPos(ImVec2(0, h * 2 / 3.f));
	ImGui::ShowMetricsWindow();
}

void GameEngine::toggleCamera() {
	m_ToggleCamera = !m_ToggleCamera;
}

bool GameEngine::IsCameraFree() const {
	return m_ToggleCamera;
}

bool GameEngine::IsEditorToggled() const {
	return m_ToggleEditor;
}

void GameEngine::changeScene(Scenes::ID tag, std::shared_ptr<Scene> scene) {
	m_CurrentScene = tag;
	if (m_SceneMap.find(tag) != m_SceneMap.end()) {
		m_SceneMap[tag] = scene;
	}
}

std::shared_ptr<Scene>& GameEngine::getCurrentScene() {
	return m_SceneMap[m_CurrentScene];
}

GLFWwindow* GameEngine::getWindow() {
	return m_Window;
}

Camera& GameEngine::getCamera(){
	return camera;
}

glm::vec2 GameEngine::getMousePos() {
	double x;
	double y;
	int w;
	int h;

	glfwGetCursorPos(m_Window, &x, &y);
	glfwGetWindowSize(m_Window, &w, &h);

	return glm::vec2(x / (w / 2.f) - 1, -y / (h / 2.f) - 1);
}

ResourceManager& GameEngine::getResources() {
	return m_Resources;
}

void GameEngine::freeCamera(GLFWwindow* window, float dt) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.ProcessKeyboard(Camera_Movement::FORWARD, dt);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.ProcessKeyboard(Camera_Movement::BACKWARD, dt);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.ProcessKeyboard(Camera_Movement::LEFT, dt);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.ProcessKeyboard(Camera_Movement::RIGHT, dt);
	}
}

void GameEngine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
	ImGuiIO& io = ImGui::GetIO();

	if (!io.WantCaptureKeyboard) {
		if (action == GLFW_PRESS || action == GLFW_RELEASE) {
			if (key == GLFW_KEY_1) {
				//glfwSetCursorPosCallback(engine->m_Window, mouse_callback);
				glfwSetInputMode(engine->m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				engine->m_ToggleEditor = false;
			}
			else if (key == GLFW_KEY_2) {
				//glfwSetCursorPosCallback(engine->m_Window, NULL);
				glfwSetInputMode(engine->m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				engine->m_ToggleEditor = true;
			}
			auto kvPair = engine->getCurrentScene()->getCommandMap().find(key);
			if (kvPair != engine->getCurrentScene()->getCommandMap().end()) {
				CommandTags::Type cmdType = glfwGetKey(window, key) == GLFW_PRESS ?
					CommandTags::Start : CommandTags::Stop;

				engine->getCurrentScene()->doCommand(Command(kvPair->second, cmdType));
			}
		}
	}
}

void GameEngine::update(float dt) {
	m_SceneMap[m_CurrentScene]->update(dt);
}

void GameEngine::resize_callback(GLFWwindow* window, int w, int h) {
	glViewport(0, 0, w, h);
}

void GameEngine::mouse_callback(GLFWwindow* window, double x, double y) {
	ImGui_ImplGlfw_CursorPosCallback(window, x, y);
	ImGuiIO& io = ImGui::GetIO();

	if (!engine->m_ToggleEditor) {
		float xpos = static_cast<float>(x);
		float ypos = static_cast<float>(y);
		if (engine->m_Start) {
			engine->m_MouseX = xpos;
			engine->m_MouseY = ypos;
			engine->m_Start = false;
		}
		float xOffset = xpos - engine->m_MouseX;
		float yOffset = engine->m_MouseY - ypos;

		engine->m_MouseX = xpos;
		engine->m_MouseY = ypos;

		engine->camera.ProcessMouseMovement(xOffset, yOffset);
	}
}

void GameEngine::mouse_click_callback(GLFWwindow* window, int button, int action, int mods) {
	ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
	ImGuiIO& io = ImGui::GetIO();

	if (!io.WantCaptureMouse) {
		if (action == GLFW_PRESS) {
			auto kvPair = engine->getCurrentScene()->getCommandMap().find(button);
			if (kvPair != engine->getCurrentScene()->getCommandMap().end()) {
				engine->getCurrentScene()->doCommand(Command(kvPair->second, CommandTags::Start));
			}
		}
		else if (action == GLFW_RELEASE) {
			auto kvPair = engine->getCurrentScene()->getCommandMap().find(button);
			if (kvPair != engine->getCurrentScene()->getCommandMap().end()) {
				engine->getCurrentScene()->doCommand(Command(kvPair->second, CommandTags::Stop));
			}
		}
	}
}

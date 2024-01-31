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

	glViewport(0, 0, 1280, 720);
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(m_Window, mouse_callback);
	glfwSetMouseButtonCallback(m_Window, mouse_click_callback);
	glfwSetKeyCallback(m_Window, key_callback);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(m_Window)) {
		glfwPollEvents();
		
		if (IsCameraFree()) {
			freeCamera(m_Window, m_DT);
		}

		m_CurTime = (float)glfwGetTime();
		engine->m_DT = m_CurTime - m_LastTime;
		m_LastTime = m_CurTime;

		glClearColor(0.52, 0.8, 0.9, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		update(m_DT);

		glfwSwapBuffers(m_Window);
	}
	glfwTerminate();
}

void GameEngine::toggleCamera() {
	m_ToggleCamera = !m_ToggleCamera;
}

bool GameEngine::IsCameraFree() const {
	return m_ToggleCamera;
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
	if (action == GLFW_PRESS || action == GLFW_RELEASE) {
		auto kvPair = engine->getCurrentScene()->getCommandMap().find(key);
		if (kvPair != engine->getCurrentScene()->getCommandMap().end()) {
			CommandTags::Type cmdType = glfwGetKey(window, key) == GLFW_PRESS ?
				CommandTags::Start : CommandTags::Stop;

			engine->getCurrentScene()->doCommand(Command(kvPair->second, cmdType));
		}
	}
}

void GameEngine::update(float dt) {
	m_SceneMap[m_CurrentScene]->update(dt);
}

void GameEngine::resize_callback(GLFWwindow* window, int w, int h) {
	
}

void GameEngine::mouse_callback(GLFWwindow* window, double x, double y) {
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

void GameEngine::mouse_click_callback(GLFWwindow* window, int button, int action, int mods) {
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

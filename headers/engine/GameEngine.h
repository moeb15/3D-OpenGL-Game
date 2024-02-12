#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "ResourceManager.h"
#include "Scene.h"
#include "SceneTags.h"
#include "glad.h"
#include "Camera.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <unordered_map>

class GameEngine {
private:
	GLFWwindow* m_Window;
	Camera camera = Camera(glm::vec3(0, 5, 12));
	float m_DT = 0.0f;
	float m_LastTime = 0.0f;
	float m_CurTime = 0.0f;
	bool m_Start;
	float m_MouseX;
	float m_MouseY;
	Scenes::ID m_CurrentScene;
	std::unordered_map<Scenes::ID, std::shared_ptr<Scene>> m_SceneMap;
	bool m_ToggleCamera;
	bool m_ToggleEditor;
	std::unordered_map<Entities::ID, bool> m_EntityPairs;
	ResourceManager m_Resources;

	static GameEngine* engine;

public:
	GameEngine();

	void run();

	Camera& getCamera();
	GLFWwindow* getWindow();
	glm::vec2 getMousePos();
	ResourceManager& getResources();
	void changeScene(Scenes::ID, std::shared_ptr<Scene>);
	std::shared_ptr<Scene>& getCurrentScene();
	void toggleCamera();
	bool IsCameraFree() const;
	bool IsEditorToggled() const;

private:
	void update(float dt);
	void freeCamera(GLFWwindow*, float);
	void sceneEditor(glm::vec3&);
	void initPairs();

	static void key_callback(GLFWwindow* window, int, int, int, int);
	static void mouse_callback(GLFWwindow*, double, double);
	static void mouse_click_callback(GLFWwindow*, int, int, int);
	static void resize_callback(GLFWwindow*, int, int);
};

#endif 

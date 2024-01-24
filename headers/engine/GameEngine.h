#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "ResourceManager.h"
#include "glad.h"
#include "Camera.h"
#include <GLFW/glfw3.h>
#include <iostream>

class GameEngine {
private:
	GLFWwindow* m_Window;
	Camera camera = Camera(glm::vec3(0, 0, 3));
	float m_DT = 0.0f;
	float m_LastTime = 0.0f;
	float m_CurTime = 0.0f;
	bool m_Start;
	float m_MouseX;
	float m_MouseY;
	
	static GameEngine* engine;

public:
	GameEngine();

	void run();

private:
	void processInput(GLFWwindow* window, float dt);
	void update(float dt);

	static void mouse_callback(GLFWwindow*, double, double);
	static void resize_callback(GLFWwindow*, int, int);
};

#endif 
